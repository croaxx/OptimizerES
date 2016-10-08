#include "FitnessFromMathExpression.h"

using namespace std;
using namespace GenericOptimizer;

auto FitnessFromMathExpression::EvaluateFitness(const vector<double>& params) const ->double
{
	double sigma = 10.0;
	double result = 1.0;
	for (unsigned i = 0; i < params.size(); i++)
	{
		result *= (exp(-params[i] * params[i] / sigma)*(1 - abs(sin(2 * params[i]))));
	}

	// do some time consuming job
	bool doTimeConsumingJob = true;
	if (doTimeConsumingJob)
	{
		long long i = 0;
		while (i < 100000)
		{
			i++;
			result += 1e-300*sqrt(result);
		}
	}

	return result;
}

