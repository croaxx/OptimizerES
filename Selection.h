#pragma once
#include <memory>
#include "RandNumbersGenerator.h"

namespace Evolutionary
{
	namespace BioMechanisms
	{
		struct ISelection
		{
			virtual auto Select()->std::vector<unsigned> = 0;
			virtual ~ISelection() {};
		};

		class UniqueParentsSelection :public ISelection
		{
		private:
			unsigned _indNum;
			std::shared_ptr<Randomness::IRandInt> _randInt;
		public:
			UniqueParentsSelection() = delete;

			UniqueParentsSelection(std::shared_ptr<Randomness::IRandInt> randInt, unsigned indicesNumber);

			virtual auto Select()->std::vector<unsigned> override;

			auto operator=(const UniqueParentsSelection & obj)->UniqueParentsSelection & = delete;
		};
	}
}
