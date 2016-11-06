#pragma once
#include <memory>
#include <atomic>
#include "GenericOptimizer\IFitness.h"
#include "Evolutionary\ISortedFitnessTable.h"

namespace GenericOptimizer
{
	class Optimizer
	{
	protected:
		std::atomic<bool> _isRunning = false;
	public:
		virtual auto StartOptimization(const std::shared_ptr<IFitness> fitObject) -> 
			std::shared_ptr<Evolutionary::ISortedFitnessTable> = 0;

		virtual auto StopOptimization()->void final
		{
			_isRunning = false;
		}

		virtual ~Optimizer() {};
	};
}