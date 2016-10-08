#include "SortedFitnessTable.h"

using namespace std;
using namespace Evolutionary;

SortedFitnessTable::SortedFitnessTable(const unsigned maxSize) :_maxSize{ maxSize } {};

auto SortedFitnessTable::AddItem(const double fitValue, const parInd& param)->bool
{
	_map.insert({ fitValue, param });
	bool isAdded = true;

	if (_map.size() > _maxSize)		// last element with the smallest key should be removed
	{
		auto it = --end(_map);		// iterator to the last entry in the table
		if ((*it).second == param)	// set isAdded to false, if the newly inserted element has the smallest key (thus is not inserted)
		{
			isAdded = false;
		}
		_map.erase(it);
	}
	return isAdded;
}

auto SortedFitnessTable::operator[](unsigned idx) const->const TableRow&
{
	auto it = begin(_map);
	advance(it, idx);
	return *it;
}

auto SortedFitnessTable::TableSize() const->unsigned
{
	return (unsigned)_map.size();
}

auto SortedFitnessTable::TableMaxSize() const->unsigned
{
	return _maxSize;
}

auto SortedFitnessTable::ValuesAtIndices(const vector<unsigned>& ind) const->vector<parInd>
{
	vector<parInd> individualsSet;
	for (unsigned i = 0; i < ind.size(); i++)
	{
		individualsSet.push_back(this->operator[](ind[i]).second);
	}
	return move(individualsSet);
}

auto SortedFitnessTable::Clear()->void
{
	_map.clear();
}

auto SortedFitnessTable::IsEmpty()->bool
{
	return _map.empty();
}
