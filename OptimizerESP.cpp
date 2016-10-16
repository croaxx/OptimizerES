#include "OptimizerESP.h"

using namespace std;
using namespace GenericOptimizer;
using namespace HelperFunctions;
using namespace Evolutionary;
using namespace Parallel;

auto OptimizerESP::StartOptimization(const shared_ptr<IFitness> fitObject)->shared_ptr<ISortedFitnessTable>
{
	_isRunning = true;		// set state to running
	_fitnessTable->Clear(); // clear the table from previous calculations, if any
	ParallelTableInitialization(fitObject); // populate table with random individuals
	
	string savePath = ReadSavePath(boost::filesystem::current_path().string() + "\\OptSetting.txt");
	// open file for writing (in append to the end of file mode)
	ofstream fileObject;
	fileObject.open(savePath, std::ios::app); 
	if (!fileObject.is_open()) throw exception("Could not open file");

	// write initialized fitness table into file
	fileObject << "Initialized fitness table (fitness; parameters; sigmas)\n";
	OptimizerES::WriteFitnessTableToFile(fileObject);

	fileObject << "Evaluated individuals\n";

	atomic<unsigned> fitCounter = _constantsESP.TableSize;

	vector<thread> workerThread;

	auto threadWork = [&](int idThread)
	{
		auto const id = idThread;
		while (fitCounter < _constantsES.MaxFitCalls)
		{
			auto newIndividual = ParamsIndividual{};
			{
				lock_guard<mutex> lock(_mutex); // to protect the read from the fitness table
				auto parentsInd = _selection->Select();
				auto selectedParents = _fitnessTable->ValuesAtIndices(parentsInd);// thread unsafe execution (protected by mutex)
				auto recombined = _recombination->Recombine(selectedParents);
				_mutation->Mutate(recombined);
				newIndividual = move(recombined);
			}

			auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are with interval [0.0,1.0]

			vector<pair<double, double>> intervalsTo;
			for (unsigned j = 0; j < _constantsES.SeachSpace.size(); j += 2)
			{
				intervalsTo.push_back(make_pair(_constantsES.SeachSpace[j], _constantsES.SeachSpace[j + 1]));
			}

			auto mappedParams = MapLinearlyToInterval(newIndividual.GetParamsRef(), intervalsFrom, intervalsTo);

			auto fitness = fitObject->EvaluateFitness(&mappedParams[0],mappedParams.size());

			lock_guard<mutex> lock(_mutex);
			if (fitCounter < _constantsES.MaxFitCalls)
			{
				_fitnessTable->AddItem(fitness, newIndividual);
				OptimizerES::WriteFitnessEntryToFile(fileObject, fitness, mappedParams, newIndividual.GetSigmasRef());
				++fitCounter;
			}
		}
	};

	for (unsigned i = 0; i < _constantsESP.LogicalProcNum; i++)
	{
		workerThread.push_back(thread(threadWork, i));
	}

	for (auto& e : workerThread)
	{
		e.join();
	}

	fileObject << "\nFinal fitness table\n";
	OptimizerES::WriteFitnessTableToFile(fileObject);
	fileObject.close();

	return _fitnessTable;
}

auto OptimizerESP::ParallelTableInitialization(const shared_ptr<IFitness> fitObj)->void
{
	vector<thread> workerThread;

	atomic<unsigned> individuals = 0; // number of created individuals so far

	auto threadWork = [&](int idThread)
	{
		auto const id = idThread;
		while (individuals < _constantsESP.TableSize)
		{
			// Generate random individual 
			auto params = GenRndParams(_rnd);

			// Generate sigma values (all equal values)
			auto sigmas = GenInitialSigmas();

			// Map parameters to search space
			auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are with interval [0.0,1.0]

			vector<pair<double, double>> intervalsTo;
			for (unsigned j = 0; j < _constantsES.SeachSpace.size(); j += 2)
			{
				intervalsTo.push_back(make_pair(_constantsES.SeachSpace[j], _constantsES.SeachSpace[j + 1]));
			}

			auto mappedParams = MapLinearlyToInterval(params, intervalsFrom, intervalsTo);

			// Evaluate fitness
			auto fitness = fitObj->EvaluateFitness(&mappedParams[0], mappedParams.size());

			lock_guard<mutex> lock(_mutex);
			if (individuals < _constantsESP.TableSize)
			{
				_fitnessTable->AddItem(fitness, ParamsIndividual{ move(params), move(sigmas) });
				++individuals;
			}
		}
	};

	for (unsigned i = 0; i < _constantsESP.LogicalProcNum; i++)
	{
		workerThread.push_back(thread(threadWork, i));
	}

	for (auto& e : workerThread)
	{
		e.join();
	}
}
