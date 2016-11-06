#pragma once
#include "Evolutionary\ESsettingsFileInteractor.h"
#include "Evolutionary\GenerationBasedES\OptimizerESGB.h"
#include "Evolutionary\SortedFitnessTable.h"


namespace Evolutionary
{
	namespace GenerationBased
	{
		class EngineGeneratorESGB
		{
		public:
			static auto WriteESGBsampleSettingToFile(const std::string& filePath) -> void;

			static auto GenerateESGBEngine(const std::string& pathFile) -> std::shared_ptr<GenericOptimizer::Optimizer>;

			static auto DisplayESGBConstants(const Evolutionary::GenerationBased::ParamsESGB& params) -> void;
		};
	}
}
