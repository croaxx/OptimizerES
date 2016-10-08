#pragma once
#include "ESsettingsFileInteractor.h"
#include "SortedFitnessTable.h"
#include "OptimizerESP.h"

namespace Evolutionary
{
	namespace GenerationBased
	{
		class EngineGeneratorESP
		{
		public:
			static auto WriteESPsampleSettingToFile(const std::string& filePath)->void;

			static auto GenerateESPEngine(const std::string& path)->std::shared_ptr<GenericOptimizer::Optimizer>;

			static auto DisplayESPConstants(const Evolutionary::Parallel::ParamsESP params)->void;
		};
	}
}
