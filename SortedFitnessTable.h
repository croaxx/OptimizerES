#pragma once
#include "ISortedFitnessTable.h"

namespace Evolutionary
{
	class SortedFitnessTable :public ISortedFitnessTable
	{
	private:
		typedef std::multimap<double, parInd, std::greater<double>> mapType;

		mapType _map = mapType{};
		unsigned _maxSize;

	public:

		explicit SortedFitnessTable(const unsigned maxSize);

		virtual auto AddItem(const double fitValue, const parInd& param)->bool override;

		virtual auto operator[](unsigned idx) const->const TableRow& override;

		virtual auto TableSize() const->unsigned override;

		virtual auto TableMaxSize() const->unsigned override;

		virtual auto ValuesAtIndices(const std::vector<unsigned>& ind) const->std::vector<parInd> override;

		virtual auto Clear()->void override;

		virtual auto IsEmpty()->bool override;
	};
}