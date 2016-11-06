#include "Evolutionary\BioMechanisms\Recombination.h"

using namespace std;
using namespace Randomness;

namespace Evolutionary
{
	namespace BioMechanisms
	{

		ProbabilisticRecombination::ProbabilisticRecombination(shared_ptr<IRandDouble> rand) : _rand{ rand } {};

		auto ProbabilisticRecombination::Recombine(const vector<ParamsIndividual>& indivSet)-> ParamsIndividual
		{
			// construct a probability-space vector
			double prob = 1.0 / indivSet.size();
			auto probabilitySpace = vector<double>{ prob };

			const auto indivNum = indivSet.size();
			for (unsigned i = 0; i < indivNum - 2; i++)
			{
				probabilitySpace.push_back(probabilitySpace[i] + prob);
			}
			probabilitySpace.push_back(1.0);// maximum probability value

			auto paramsFirstIndiv = indivSet[0].CopyParams();
			decltype(paramsFirstIndiv) paramsRecombined;

			// Recombine Params by a probability rule
			for (unsigned i = 0; i < paramsFirstIndiv.size(); i++)
			{
				auto rnd = _rand->NextRand();

				int index = -1;
				auto indParent = find_if(begin(probabilitySpace), end(probabilitySpace), [&rnd, &index](double x)
				{
					++index;
					return rnd < x;
				});

				paramsRecombined.push_back(indivSet[index].GetParamsRef().at(i));
			}

			// Recombine sigma by simple averaging
			auto sigmasFirstIndiv = indivSet[0].CopySigmas();
			const auto sigmaLength = sigmasFirstIndiv.size();
			decltype(sigmasFirstIndiv) sigmaRecombined;

			for (unsigned i = 0; i < sigmaLength; i++)
			{
				double sum = 0.0;
				for (unsigned j = 0; j < indivNum; j++)
				{
					sum += indivSet[j].GetSigmasRef().at(i);
				}
				sum /= indivNum;
				sigmaRecombined.push_back(sum);
			}

			return ParamsIndividual{ move(paramsRecombined), move(sigmaRecombined) };
		}
	}
}