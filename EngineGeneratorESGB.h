#pragma once
#include "ESsettingsFileInteractor.h"
#include "OptimizerESGB.h"
#include "SortedFitnessTable.h"


namespace Evolutionary
{
	namespace GenerationBased
	{
		class EngineGeneratorESGB
		{
		public:
			static auto WriteESGBsampleSettingToFile(const std::string& filePath)->void;

			static auto GenerateESGBEngine(const std::string& pathFile)->std::shared_ptr<GenericOptimizer::Optimizer>;

			static auto DisplayESGBConstants(const Evolutionary::GenerationBased::ParamsESGB& params)->void;
		};
	}
}
