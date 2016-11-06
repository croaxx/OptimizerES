#pragma once
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "Evolutionary\ParamsES.h"
#include "HelperFunctions\HelperFunctions.h"

namespace Evolutionary
{
	class ESsettingsFileInteractor
	{
	public:
		static auto WriteSampleESsettingsToFile(const std::string& path) -> std::ofstream;

		static auto InitializeESConstants(const std::vector<std::string>& inputParams) -> Evolutionary::ParamsES;

		static auto DisplayESConstants(const Evolutionary::ParamsES& params) -> void;
	};
}