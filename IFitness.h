#pragma once
#include <vector>

namespace GenericOptimizer
{
	// Every fitness evaluator class should implement this interface
	struct IFitness
	{
		virtual auto EvaluateFitness(const std::vector<double>& params) const->double = 0;
		virtual ~IFitness() {};
	};
}