#pragma once
#include <fstream>
#include <mutex>
#include "Evolutionary\OptimizerES.h"
#include "Evolutionary\Parallel\ParamsESP.h"
#include "Evolutionary\BioMechanisms\Mutation.h"
#include "Evolutionary\BioMechanisms\Selection.h"
#include "Evolutionary\BioMechanisms\Recombination.h"


namespace Evolutionary
{
	namespace Parallel
	{
		class OptimizerESP :public OptimizerES
		{
		private:
			const ParamsESP _constantsESP;
			std::shared_ptr<Randomness::IRandDouble>_rnd;
			std::shared_ptr<BioMechanisms::ISelection> _selection;
			std::shared_ptr<BioMechanisms::IRecombination> _recombination;
			std::shared_ptr<BioMechanisms::IMutation> _mutation;
			std::mutex _mutex; // used to lock read-write access into the shared table

			auto ParallelTableInitialization(const std::shared_ptr<GenericOptimizer::IFitness> fitObj)->void;

		public:
			OptimizerESP(std::shared_ptr<ISortedFitnessTable> table,
						 const ParamsES constantsES,
						 const ParamsESP constantsESP,
						 std::shared_ptr<Randomness::IRandDouble> rnd,
						 std::shared_ptr<BioMechanisms::ISelection> selection,
						 std::shared_ptr<BioMechanisms::IRecombination> recombination,
						 std::shared_ptr<BioMechanisms::IMutation> mutation):
				OptimizerES{ table, constantsES }, _constantsESP{ constantsESP }, _rnd{ rnd },
				_selection{ selection }, _recombination{ recombination }, _mutation{ mutation } {};

			virtual auto StartOptimization(const std::shared_ptr<GenericOptimizer::IFitness> fitObject) -> 
				std::shared_ptr<Evolutionary::ISortedFitnessTable>;

		};
	}
}