#pragma once
#include "Evolutionary\OptimizerES.h"
#include "Evolutionary\GenerationBasedES\ParamsESGB.h"
#include "Evolutionary\BioMechanisms\Mutation.h"
#include "Evolutionary\BioMechanisms\Selection.h"
#include "Evolutionary\BioMechanisms\Recombination.h"

namespace Evolutionary
{
	namespace GenerationBased
	{
		class OptimizerESGB: public OptimizerES
		{
		private:
			ParamsESGB _constantsESGB;
			std::shared_ptr<Randomness::IRandDouble>_rnd;
			std::shared_ptr<BioMechanisms::ISelection> _selection;
			std::shared_ptr<BioMechanisms::IRecombination> _recombination;
			std::shared_ptr<BioMechanisms::IMutation> _mutation;
			
			auto TableInitialization(const std::shared_ptr<GenericOptimizer::IFitness> fitObj) -> void;
		public:
			OptimizerESGB() = delete;

			OptimizerESGB(std::shared_ptr<ISortedFitnessTable> table, 
						  const ParamsES constantsES,
						  const ParamsESGB constantsESGB,
						  std::shared_ptr<Randomness::IRandDouble> rnd, 
						  std::shared_ptr<BioMechanisms::ISelection> selection,
						  std::shared_ptr<BioMechanisms::IRecombination> recombination, 
						  std::shared_ptr<BioMechanisms::IMutation> mutation);

			virtual auto StartOptimization(const std::shared_ptr<GenericOptimizer::IFitness> fitObject) -> 
				std::shared_ptr<Evolutionary::ISortedFitnessTable>;
		};
	}
}