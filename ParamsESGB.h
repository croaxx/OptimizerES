#pragma once

namespace Evolutionary
{
	namespace GenerationBased
	{
		class ParamsESGB
		{
		public:
			const unsigned ParentsNumber;
			const unsigned ChildrenNumber;

			ParamsESGB(const unsigned parentsNumber, const unsigned childrenNumber) :
				ParentsNumber{ parentsNumber }, ChildrenNumber{ childrenNumber } {}

			ParamsESGB() = delete;

			auto operator=(const ParamsESGB & obj)->ParamsESGB & = delete;
		};
	}
}

