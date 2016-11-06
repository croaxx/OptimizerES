#pragma once
#include <iostream>
#include <conio.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "GenericOptimizer\Optimizer.h"
#include "Evolutionary\GenerationBasedES\EngineGeneratorESGB.h"
#include "Evolutionary\Parallel\EngineGeneratorESP.h"

namespace GenericOptimizer
{
	class OptimizerFactory
	{
	public:
		static auto GenerateOptimizationEngine()->std::shared_ptr<GenericOptimizer::Optimizer>;
	};
}

