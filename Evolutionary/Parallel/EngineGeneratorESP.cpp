#include "Evolutionary\Parallel\EngineGeneratorESP.h"

using namespace std;
using namespace GenericOptimizer;
using namespace HelperFunctions;
using namespace Randomness;
using namespace Evolutionary::BioMechanisms;

namespace Evolutionary
{
	namespace Parallel
	{

		auto EngineGeneratorESP::WriteESPsampleSettingToFile(const string& filePath) -> void
		{
			// Write generic ES sample settings to file 
			auto file = ESsettingsFileInteractor::WriteSampleESsettingsToFile(filePath);

			// Write ESGB specific settings to file
			file << "Table size\n";
			file << "5\n";
			file << "Parallelization degree, 0 - max number of logical processors in the machine\n";
			file << "0\n";
			file.close();
		}

		auto EngineGeneratorESP::GenerateESPEngine(const string& path)->shared_ptr<Optimizer>
		{
			srand(time(0));
			unsigned seed = rand(); //5489u; // seed for random number generator

			auto inputParams = ReadFileContext(path, "oddLines");

			auto constsES = ESsettingsFileInteractor::InitializeESConstants(inputParams);

			ESsettingsFileInteractor::DisplayESConstants(constsES);

			unsigned processes = (unsigned)stoi(inputParams[7].c_str());

			if (processes == 0) processes = thread::hardware_concurrency();

			auto constsESP = ParamsESP{ (unsigned)stoi(inputParams[6].c_str()), processes };

			DisplayESPConstants(constsESP);

			// Set the fitness table, and random engines
			shared_ptr<ISortedFitnessTable> instTable = make_shared<SortedFitnessTable>(constsESP.TableSize);

			shared_ptr <IRandInt> instMtInt = make_shared<MersenneTwisterInt>(0, constsESP.TableSize - 1, seed);

			shared_ptr<IRandDouble> instMtStdNorm = make_shared<MersenneTwisterStdNorm>(seed);

			shared_ptr<IRandDouble> instMtDouble = make_shared<MersenneTwisterUniformDouble>(0.0, 1.0, seed);

			// Set selection, recombination and mutation engines
			shared_ptr<ISelection> instSelection = make_shared<UniqueParentsSelection>(instMtInt,
																					   constsES.NumberOfRecombParents);

			shared_ptr<IRecombination>  instRecomb = make_shared<ProbabilisticRecombination>(instMtDouble);

			shared_ptr<IMutation>  instMutation = make_shared< StandardMutation>(instMtStdNorm, constsES.Tau0, constsES.Tau1);

			// Set the optimization engine, by putting all together
			shared_ptr<Optimizer> engineESP = make_shared<OptimizerESP>(instTable, constsES, constsESP, instMtDouble,
																		instSelection, instRecomb, instMutation);

			return engineESP;
		}

		auto EngineGeneratorESP::DisplayESPConstants(const ParamsESP params)->void
		{
			printf("Table size: %d\n", params.TableSize);
			printf("Parallelization over logical cores: %d\n", params.LogicalProcNum);
		}

	}
}