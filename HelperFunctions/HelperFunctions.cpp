#include "HelperFunctions\HelperFunctions.h"

using namespace std;

namespace HelperFunctions
{

	auto MapLinearlyToInterval(const vector<double>& values, const pair<double, double>& intervalFrom,
							   const vector<pair<double, double>>& intervalsTo) -> vector<double>
	{
		if (values.size() != intervalsTo.size())
		{
			string s = "Error in function '";
			s = s + __func__ + "' \nsize of the values set must be equal to the set intervals";
			throw exception(s.c_str());
		}

		vector<double> mapped(values.size());
		for (unsigned i = 0; i < mapped.size(); i++)
		{
			double a1 = (intervalsTo[i].second - intervalsTo[i].first);
			double a2 = (intervalFrom.second*intervalsTo[i].first - intervalFrom.first*intervalsTo[i].second);
			mapped[i] = (a1*values[i] + a2) / (intervalFrom.second - intervalFrom.first);
		}
		return move(mapped);
	}

	auto ReadFileContext(const string& path, const string& specifier = "allLines") -> vector<string>
	{
		string line;
		vector<string> context;

		ifstream file(path);
		if (!file.is_open()) throw exception("Could not open file for reading.");

		unsigned counter = 0;
		while (getline(file, line))
		{
			if (specifier == "allLines")
			{
				context.push_back(line);
			}
			else if (specifier == "evenLines" && counter % 2 == 0)
			{
				context.push_back(line);
			}
			else if (specifier == "oddLines" && counter % 2 != 0)
			{
				context.push_back(line);
			}
			counter++;
		}
		file.close();

		return move(context);
	}

	auto ClearConsoleWindow()->void
	{
		// TODO implement linux clear console
		// So far only windows
		#if defined(_WIN64) || defined(_WIN32)	
		system("cls");
		#endif
	}

}