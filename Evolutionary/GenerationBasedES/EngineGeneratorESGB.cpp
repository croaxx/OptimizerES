#include "Evolutionary\GenerationBasedES\EngineGeneratorESGB.h"

using namespace std;
using namespace GenericOptimizer;
using namespace HelperFunctions;
using namespace Randomness;
using namespace Evolutionary::BioMechanisms;

namespace Evolutionary
{
	namespace GenerationBased
	{
		auto EngineGeneratorESGB::WriteESGBsampleSettingToFile(const string& filePath) -> void
		{
			// Write generic ES sample settings to file 
			ofstream file = ESsettingsFileInteractor::WriteSampleESsettingsToFile(filePath);

			// Write ESGB specific settings to file
			file << "Number of parents\n";
			file << "7\n";
			file << "Number of children in generation\n";
			file << "30\n";
			file.close();
		}

		auto EngineGeneratorESGB::DisplayESGBConstants(const ParamsESGB& params) -> void
		{
			printf("Number of parents in each generation: %d\n", params.ParentsNumber);
			printf("Number of children in generation: %d\n", params.ChildrenNumber);
		}

		auto EngineGeneratorESGB::GenerateESGBEngine(const string& pathFile) -> shared_ptr<Optimizer>
		{
			srand(time(0));
			unsigned seed = rand(); //5489u; // seed for random number generators

			// Parse optimization parameters from the pathFile
			auto inputParams = ReadFileContext(pathFile, "oddLines");

			auto constsES = ESsettingsFileInteractor::InitializeESConstants(inputParams);
			ESsettingsFileInteractor::DisplayESConstants(constsES);

			auto constsESGB = ParamsESGB{ (unsigned)stoi(inputParams[6].c_str()), 
										  (unsigned)stoi(inputParams[7].c_str()) };

			DisplayESGBConstants(constsESGB);

			// Set the fitness table
			shared_ptr<ISortedFitnessTable> instTable = make_shared<SortedFitnessTable> (constsESGB.ParentsNumber);

			// Set random engines
			shared_ptr<IRandInt> instMtInt = make_shared<MersenneTwisterInt> (0, constsESGB.ParentsNumber - 1, seed);

			shared_ptr<IRandDouble> instMtStdNorm = make_shared<MersenneTwisterStdNorm> (seed);

			shared_ptr<IRandDouble> instMtDouble = make_shared<MersenneTwisterUniformDouble> (0.0, 1.0, seed);

			// Set selection, recombination and mutation engines
			shared_ptr<ISelection> instSelection = make_shared<UniqueParentsSelection> (instMtInt, 
																						constsES.NumberOfRecombParents);

			shared_ptr<IRecombination>  instRecomb = make_shared<ProbabilisticRecombination> (instMtDouble);

			shared_ptr<IMutation>  instMutation = make_shared< StandardMutation> (instMtStdNorm, constsES.Tau0,
																				  constsES.Tau1);
			// Set the optimization engine, by putting all together
			shared_ptr<Optimizer> engineESGB = make_shared<OptimizerESGB> (instTable, constsES, constsESGB, instMtDouble,
																		   instSelection, instRecomb, instMutation);
			return move(engineESGB);
		}

	}
}