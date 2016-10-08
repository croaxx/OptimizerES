#pragma once
#include "IFitness.h"

namespace GenericOptimizer
{
	class FitnessFromMathExpression : public IFitness
	{
	public:
		virtual auto IFitness::EvaluateFitness(const std::vector<double>& params) const ->double;
		virtual ~FitnessFromMathExpression() {};
	};
}