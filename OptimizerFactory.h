#pragma once
#include <iostream>
#include <conio.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "Optimizer.h"
#include "EngineGeneratorESGB.h"
#include "EngineGeneratorESP.h"

class OptimizerFactory
{
public:
	static auto GenerateOptimizationEngine()->std::shared_ptr<GenericOptimizer::Optimizer>;
};

