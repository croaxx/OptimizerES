#pragma once
#include <random>

namespace Randomness
{
	struct IRandInt
	{
		virtual auto NextRand()->int = 0;
		virtual ~IRandInt() {};
	};

	struct IRandDouble
	{
		virtual auto NextRand()->double = 0;
		virtual ~IRandDouble() {};
	};

	class MersenneTwisterInt :public IRandInt
	{
	private:
		std::mt19937_64 _mt;	// an engine (Mersenne twister)
		std::uniform_int_distribution<int> _distribution;
	public:

		MersenneTwisterInt() = delete;

		MersenneTwisterInt(int min, int max, unsigned __int64 mt);

		virtual auto NextRand()->int override;
		
	};

	class MersenneTwisterUniformDouble :public IRandDouble
	{
	private:
		std::mt19937_64 _mt;		// an engine (Mersenne twister)
		std::uniform_real_distribution<double> _distribution;
	public:

		MersenneTwisterUniformDouble() = delete;

		MersenneTwisterUniformDouble(double min, double max, unsigned __int64 mt);

		virtual auto NextRand()->double override;
		
	};

	class MersenneTwisterStdNorm :public IRandDouble
	{
	private:
		std::mt19937_64 _mt;		// an engine (Mersenne twister)
		std::normal_distribution<double> _distribution;
	public:

		MersenneTwisterStdNorm() = delete;

		explicit MersenneTwisterStdNorm(unsigned __int64 mt);

		virtual auto NextRand()->double override;

	};

}
