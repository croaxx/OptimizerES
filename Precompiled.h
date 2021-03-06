#pragma once

#include <thread>
#include <numeric>
#include <future>
#include <random>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "ASSERT_TRACE_VERIFY.h"
#include "HelperFunctions\HelperFunctions.h"
#include "GenericOptimizer\IFitness.h"
#include "GenericOptimizer\FitnessFromMathExpression.h"
#include "Evolutionary\ParamsES.h"
#include "Evolutionary\ParamsIndividual.h"
#include "Evolutionary\ISortedFitnessTable.h"
#include "Evolutionary\SortedFitnessTable.h"
#include "Randomness\RandNumbersGenerator.h"
#include "Evolutionary\BioMechanisms\Mutation.h"
#include "Evolutionary\BioMechanisms\Recombination.h"
#include "Evolutionary\BioMechanisms\Selection.h"
#include "Evolutionary\GenerationBasedES\ParamsESGB.h"
#include "GenericOptimizer\Optimizer.h"
#include "Evolutionary\OptimizerES.h"
#include "Evolutionary\GenerationBasedES\OptimizerESGB.h"
#include "Evolutionary\Parallel\OptimizerESP.h"
#include "Evolutionary\ESsettingsFileInteractor.h"
#include "Evolutionary\GenerationBasedES\EngineGeneratorESGB.h"
#include "Evolutionary\Parallel\EngineGeneratorESP.h"
#include "GenericOptimizer\OptimizerFactory.h"
#include "FitnessLibrary.h"