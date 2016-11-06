#include "Evolutionary\BioMechanisms\Mutation.h"

using namespace std;
using namespace Randomness;

namespace Evolutionary
{
	namespace BioMechanisms
	{

		StandardMutation::StandardMutation(shared_ptr<IRandDouble> rand, const double tau0, const double tau1):
			_rand{ rand }, _tau0{ tau0 }, _tau1{ tau1 } {};

		auto StandardMutation::Mutate(ParamsIndividual& indiv) -> void
		{
			// Mutate Sigma
			double rnd = _rand->NextRand();
			double commonFactor = exp(_tau0*rnd);
			auto sigmas = indiv.CopySigmas();
			auto params = indiv.CopyParams();
			for_each(begin(sigmas), end(sigmas), [&](decltype(sigmas[0]) s)
			{
				rnd = _rand->NextRand();
				double sepFactor = exp(_tau1*rnd);
				s *= commonFactor*sepFactor;
			});

			// Mutate Params
			for (unsigned i = 0; i < indiv.GetParamsSize(); i++)
			{
				rnd = _rand->NextRand();

				if (sigmas.size() == params.size()) // sigma is vector
				{
					params[i] += sigmas[i] * rnd;
				}
				else if (sigmas.size() == 1) // sigma is a scalar
				{
					params[i] += sigmas[0] * rnd;
				}
				else // inappropriate length of sigma
				{
					throw length_error("Exception in: " __FUNCTION__ " - size of sigma - vector is not appropriate.\n");
				}

				// check that parameters are inside the bounds (0.0,1.0), if not assign the boundary value 
				params[i] = (std::min)(1.0, params[i]); // extra parenthesis to avoid macro invocation during debugging
				params[i] = (std::max)(0.0, params[i]);
			}

			// assign mutated values to the individual 
			indiv.SetParams(params);
			indiv.SetSimgas(sigmas);
		}

	}
}

