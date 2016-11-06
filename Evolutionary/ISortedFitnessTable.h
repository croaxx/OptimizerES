#pragma once
#include <map>
#include <functional>
#include "Evolutionary\ParamsIndividual.h"


namespace Evolutionary
{
	struct ISortedFitnessTable
	{
		using parInd = ParamsIndividual;
		using TableRow = std::pair<const double, parInd>;

		virtual auto operator[](unsigned idx) const -> const TableRow& = 0;
		virtual auto AddItem(const double fitValue, const parInd& param) -> bool = 0;
		virtual auto TableSize() const -> unsigned = 0;
		virtual auto TableMaxSize() const -> unsigned = 0;
		virtual auto ValuesAtIndices(const std::vector<unsigned>& ind) const -> std::vector<parInd> = 0;
		virtual auto Clear() -> void = 0;
		virtual auto IsEmpty() const -> bool = 0;
		virtual ~ISortedFitnessTable() {};
	};
}