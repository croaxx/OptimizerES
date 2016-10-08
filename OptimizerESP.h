#pragma once
#include <fstream>
#include <mutex>
#include "OptimizerES.h"
#include "ParamsESP.h"
#include "Mutation.h"
#include "Selection.h"
#include "Recombination.h"


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
			auto ParallelTableInitialization(const GenericOptimizer::IFitness& fitObj)->void;
		public:
			OptimizerESP(std::shared_ptr<ISortedFitnessTable> table, const ParamsES constantsES, const ParamsESP constantsESP,
				std::shared_ptr<Randomness::IRandDouble> rnd, std::shared_ptr<BioMechanisms::ISelection> selection,
				std::shared_ptr<BioMechanisms::IRecombination> recombination, std::shared_ptr<BioMechanisms::IMutation> mutation) :
				OptimizerES{ table, constantsES }, _constantsESP{ constantsESP }, _rnd{ rnd }, _selection{ selection },
				_recombination{ recombination }, _mutation{ mutation } {};

			virtual auto StartOptimization(const GenericOptimizer::IFitness& fitObject)->std::shared_ptr<Evolutionary::ISortedFitnessTable> override;

		};
	}
}