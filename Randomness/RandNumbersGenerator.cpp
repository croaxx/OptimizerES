#include "Randomness\RandNumbersGenerator.h"

namespace Randomness
{

	MersenneTwisterInt::MersenneTwisterInt(int min, int max, unsigned __int64 mt): _distribution{ min, max }, _mt{ mt } {};

	auto MersenneTwisterInt::NextRand()->int
	{
		return _distribution(_mt);
	}

	MersenneTwisterUniformDouble::MersenneTwisterUniformDouble(double min, double max, unsigned __int64 mt):
		_distribution{ min, max }, _mt{ mt } {};

	auto MersenneTwisterUniformDouble::NextRand()->double
	{
		return _distribution(_mt);
	}

	MersenneTwisterStdNorm::MersenneTwisterStdNorm(unsigned __int64 mt) :_distribution{ 0.0, 1.0 }, _mt{ mt } {};

	auto MersenneTwisterStdNorm::NextRand()->double
	{
		return _distribution(_mt);
	}

}