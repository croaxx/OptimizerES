#pragma once
#include <memory>
#include <algorithm>
#include "Evolutionary\ParamsIndividual.h"
#include "Randomness\RandNumbersGenerator.h"


namespace Evolutionary
{
	namespace BioMechanisms
	{

		struct IMutation
		{
			virtual auto Mutate(Evolutionary::ParamsIndividual& indiv) -> void = 0;
			virtual ~IMutation() {};
		};

		class StandardMutation: public IMutation
		{
		private:
			std::shared_ptr<Randomness::IRandDouble> _rand;
			double _tau0;
			double _tau1;
		public:
			StandardMutation() = delete;

			StandardMutation(std::shared_ptr<Randomness::IRandDouble> rand, 
							 const double tau0, const double tau1);

			virtual auto Mutate(Evolutionary::ParamsIndividual& indiv) -> void;

			auto operator=(const StandardMutation& obj) -> StandardMutation& = delete;
		};

	}
}
