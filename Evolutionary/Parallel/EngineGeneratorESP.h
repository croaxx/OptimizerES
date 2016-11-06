#pragma once
#include "Evolutionary\ESsettingsFileInteractor.h"
#include "Evolutionary\SortedFitnessTable.h"
#include "Evolutionary\Parallel\OptimizerESP.h"

namespace Evolutionary
{
	namespace Parallel
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
