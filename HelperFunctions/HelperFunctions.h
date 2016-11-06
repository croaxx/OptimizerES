#pragma once
#include <vector>
#include <fstream>
#include <string>

namespace HelperFunctions
{
	// Maps a set of values all given in [a,b] interval to a set of different intervals [c_i,d_i], using linear transformation
	auto MapLinearlyToInterval(const std::vector<double>& values, const std::pair<double, double>& intervalFrom,
							   const std::vector<std::pair<double, double>>& intervalsTo) -> std::vector<double>;

	// Read file context, specifier = 'oddLines', 'evenLines', 'allLines'
	auto ReadFileContext(const std::string& path, const std::string& specifier) -> std::vector<std::string>;

	auto ClearConsoleWindow() -> void;
}