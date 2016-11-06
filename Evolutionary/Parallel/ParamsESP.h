#pragma once

namespace Evolutionary
{
	namespace Parallel
	{
		class ParamsESP
		{
		public:
			const unsigned TableSize;
			const unsigned LogicalProcNum;

			ParamsESP() = delete;

			ParamsESP(const unsigned tableSize, const unsigned logicalProcNum):
				TableSize{ tableSize }, LogicalProcNum{ logicalProcNum } {}

			auto operator=(const ParamsESP& obj)->ParamsESP& = delete; // absence of this line causes a compiler warning
		};
	}
}