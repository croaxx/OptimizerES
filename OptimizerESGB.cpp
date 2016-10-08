#include "OptimizerESGB.h"

using namespace std;
using namespace Evolutionary;
using namespace BioMechanisms;
using namespace GenerationBased;
using namespace Randomness;
using namespace GenericOptimizer;
using namespace HelperFunctions;

OptimizerESGB::OptimizerESGB(shared_ptr<ISortedFitnessTable> table, 
	const ParamsES constantsES, const ParamsESGB constantsESGB,	shared_ptr<IRandDouble> rnd, 
	shared_ptr<ISelection> selection, shared_ptr<IRecombination> recombination, shared_ptr<IMutation> mutation) :
	OptimizerES{ table, constantsES }, _constantsESGB{ constantsESGB }, _rnd{ rnd }, _selection{ selection },
	_recombination{ recombination }, _mutation{ mutation } {};

auto OptimizerESGB::StartOptimization(const IFitness& fitObject)->shared_ptr<ISortedFitnessTable>
{
	_isRunning = true;
	_fitnessTable->Clear();
	TableInitialization(fitObject); // populate fitness table with random individuals

	// get the save path from the settings file
	string savePath = ReadSavePath(boost::filesystem::current_path().string() + "\\OptSetting.txt");
	// open file for writing (append lines to the end of file)
	ofstream fileObject;
	fileObject.open(savePath, std::ios::app);
	if (!fileObject.is_open()) throw exception("Could not open file");

	// write initialized fitness table into file
	fileObject << "Initialized fitness table (fitness; parameters; sigmas)\n";
	OptimizerES::WriteFitnessTableToFile(fileObject);

	fileObject << "Evaluated individuals\n";

	unsigned fitCounter = _constantsESGB.ParentsNumber;

	// Main loop - Select parents, recombine them, and mutate the offspring
	while (fitCounter < _constantsES.MaxFitCalls)
	{
		if (_isRunning == false)
		{
			printf("Optimization stopped by the user...\n");
			break;
		}

		// Compute all children in one generation
		vector<double> fitnesses;
		vector<ParamsIndividual> children;
		for (unsigned j = 0; j < _constantsESGB.ChildrenNumber; j++)
		{
			auto parentsInd = _selection->Select();

			auto selectedParents = _fitnessTable->ValuesAtIndices(parentsInd);

			auto recombined = _recombination->Recombine(selectedParents);

			_mutation->Mutate(recombined);

			//linear mapping of the parameters (of the recombined offspring) to the searchspace
			auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are with interval [0.0,1.0]

			vector<pair<double, double>> intervalsTo;
			for (unsigned i = 0; i < _constantsES.SeachSpace.size(); i += 2)
			{
				intervalsTo.push_back(make_pair(_constantsES.SeachSpace[i], _constantsES.SeachSpace[i + 1]));
			}

			auto mappedParams = MapLinearlyToInterval(recombined.GetParamsRef(), intervalsFrom, intervalsTo);
			//evaluate the fitness 
			fitnesses.push_back(fitObject.EvaluateFitness(mappedParams));
			OptimizerES::WriteFitnessEntryToFile(fileObject, fitnesses.back(), mappedParams, recombined.GetSigmasRef());
			++fitCounter;
			children.push_back(move(recombined));
		}

		// Add new children to the fitness table
		for (unsigned i = 0; i < _constantsESGB.ChildrenNumber; i++)
		{
			_fitnessTable->AddItem(move(fitnesses[i]), move(children[i]));
		}
	}

	fileObject << "\nFinal fitness table\n";
	OptimizerES::WriteFitnessTableToFile(fileObject);
	fileObject.close();

	return _fitnessTable;
}


auto OptimizerESGB::TableInitialization(const IFitness& fitObj)->void
{
	for (unsigned i = 0; i < _constantsESGB.ParentsNumber; i++)
	{
		// Generate random individual 
		auto params = GenRndParams(_rnd);

		// Generate initial sigma values (all equal values)
		auto sigmas = GenInitialSigmas();

		auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are with interval [0.0,1.0]
		vector<pair<double, double>> intervalsTo;
		for (unsigned j = 0; j < _constantsES.SeachSpace.size(); j += 2)
		{
			intervalsTo.push_back(make_pair(_constantsES.SeachSpace[j], _constantsES.SeachSpace[j + 1]));
		}

		auto mappedParams = MapLinearlyToInterval(params, intervalsFrom, intervalsTo);

		auto fitness = fitObj.EvaluateFitness(mappedParams);

		_fitnessTable->AddItem(fitness, ParamsIndividual{ move(params), move(sigmas) });
	}
}