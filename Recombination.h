#pragma once
#include <memory>
#include <algorithm>
#include "ParamsIndividual.h"
#include "RandNumbersGenerator.h"

namespace Evolutionary
{
	namespace BioMechanisms
	{
		struct IRecombination
		{
			virtual auto Recombine(const std::vector<Evolutionary::ParamsIndividual>& indivSet)->Evolutionary::ParamsIndividual = 0;
			virtual ~IRecombination() {};
		};

		class ProbabilisticRecombination :public IRecombination
		{
		private:
			std::shared_ptr<Randomness::IRandDouble> _rand;
		public:
			explicit ProbabilisticRecombination(std::shared_ptr<Randomness::IRandDouble> rand);

			virtual auto Recombine(const std::vector<Evolutionary::ParamsIndividual>& indivSet)->Evolutionary::ParamsIndividual override;

			auto operator=(const ProbabilisticRecombination & obj)->ProbabilisticRecombination & = delete;
		};
	}
}