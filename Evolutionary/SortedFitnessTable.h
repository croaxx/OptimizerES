#pragma once
#include "Evolutionary\ISortedFitnessTable.h"

namespace Evolutionary
{
	class SortedFitnessTable: public ISortedFitnessTable
	{
	private:
		using mapType = std::multimap<double, parInd, std::greater<double>>;

		mapType _map = mapType{};
		unsigned _maxSize;

	public:

		explicit SortedFitnessTable(const unsigned maxSize);

		virtual auto AddItem(const double fitValue, const parInd& param) -> bool;

		virtual auto operator[](unsigned idx) const -> const TableRow&;

		virtual auto TableSize() const -> unsigned;

		virtual auto TableMaxSize() const -> unsigned;

		virtual auto ValuesAtIndices(const std::vector<unsigned>& ind) const -> std::vector<parInd>;

		virtual auto Clear() -> void;

		virtual auto IsEmpty() const -> bool;
	};
}