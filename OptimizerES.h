#pragma once
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "Optimizer.h"
#include "ParamsES.h"
#include "HelperFunctions.h"
#include "RandNumbersGenerator.h"

namespace Evolutionary
{
	class OptimizerES :public GenericOptimizer::Optimizer
	{
	protected:
		std::shared_ptr<ISortedFitnessTable> _fitnessTable;
		const ParamsES _constantsES;
		typedef std::chrono::high_resolution_clock Clock;

		OptimizerES(std::shared_ptr<ISortedFitnessTable> fitnessTable, const ParamsES& constantsES);

		auto DisplayFitnessTable() const-> void;

		auto WriteFitnessTableToFile(std::ofstream& fileObject) const->void;

		auto WriteFitnessEntryToFile(std::ofstream& fileObject, const double& fitness, const std::vector<double>& mappedPrams,
			const std::vector<double>& sigmas) const->void;

		static auto ReadSavePath(const std::string& settingFilePath)->std::string;

		auto GenRndParams(std::shared_ptr<Randomness::IRandDouble> rnd) const->
			decltype(std::declval<Evolutionary::ParamsIndividual>().CopyParams());

		auto GenInitialSigmas() const->decltype(std::declval<Evolutionary::ParamsIndividual>().CopySigmas());

		auto operator=(const OptimizerES & obj)->OptimizerES & = delete;
	};
}