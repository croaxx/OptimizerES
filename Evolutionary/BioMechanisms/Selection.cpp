#include "Evolutionary\BioMechanisms\Selection.h"

using namespace std;
using namespace Randomness;

namespace Evolutionary
{
	namespace BioMechanisms
	{

		UniqueParentsSelection::UniqueParentsSelection(shared_ptr<IRandInt> randInt, unsigned indicesNumber) :
			_indNum{ indicesNumber }, _randInt{ std::move(randInt) } {};

		auto UniqueParentsSelection::Select() -> vector<unsigned>
		{
			vector<unsigned> parents;

			while (parents.size() != _indNum)						// generate parents until all unique are found
			{
				auto rnd = _randInt->NextRand();
				auto it = find(begin(parents), end(parents), rnd);	// check for uniqueness
				if (it == end(parents))
				{
					parents.push_back(rnd);
				}
			}

			return move(parents);
		}

	}
}