#pragma once
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "ParamsES.h"
#include "HelperFunctions.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace Evolutionary
{
	class ESsettingsFileInteractor
	{
	public:
		auto static WriteSampleESsettingsToFile(const std::string& path)->std::ofstream;

		auto static InitializeESConstants(const std::vector<std::string>& inputParams)->Evolutionary::ParamsES;

		static auto DisplayESConstants(const Evolutionary::ParamsES& params)->void;
	};
}