#pragma once
#include "IFitness.h"

namespace GenericOptimizer
{
	class FitnessFromMathExpression : public IFitness
	{
	public:
		virtual auto IFitness::EvaluateFitness(const double* params, unsigned lengthParams) const ->double;
		virtual ~FitnessFromMathExpression() {};
	};
}