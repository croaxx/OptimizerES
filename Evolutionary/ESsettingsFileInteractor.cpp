#include "Evolutionary\ESsettingsFileInteractor.h"

using namespace std;
using namespace HelperFunctions;

namespace Evolutionary
{

	auto ESsettingsFileInteractor::WriteSampleESsettingsToFile(const string& path) -> ofstream
	{
		ofstream sampleFile(path, ofstream::trunc);
		if (!sampleFile.is_open()) throw exception("Could not open file");

		sampleFile << "Save results in a file:\n";
		sampleFile << boost::filesystem::current_path().string() + "\\OptimizationResults.txt\n";
		sampleFile << "Parameters search space - min1,max1,min2,max2 (comma separated)\n";
		sampleFile << "-6.0,3.0,-6.0,3.0,-6.0,3.0,-6.0,3.0,-6.0,3.0\n";
		sampleFile << "Maximum number of fitness calls\n";
		sampleFile << "1500\n";
		sampleFile << "Is sigma vector (0 - false, 1 - true)\n";
		sampleFile << "1\n";
		sampleFile << "Initial sigma\n";
		sampleFile << "0.3\n";
		sampleFile << "Number of coupling parents\n";
		sampleFile << "2\n";

		return sampleFile;
	}

	auto ESsettingsFileInteractor::InitializeESConstants(const vector<string>& inputParams) -> ParamsES
	{
		vector<double> searchSpace;
		unsigned maxFitCalls;
		bool isSigmaVector;
		double sigmaInitial;
		unsigned numberOfRecombParents;
		double tau0;
		double tau1;

		{
			vector<string> strs;
			boost::split(strs, inputParams[1], boost::is_any_of(","));
			for (auto const& e : strs)
			{
				searchSpace.push_back(atof(e.c_str()));
			}
		}

		maxFitCalls = stoi(inputParams[2].c_str());
		isSigmaVector = static_cast<bool>(stoi(inputParams[3].c_str()));
		sigmaInitial = atof(inputParams[4].c_str());
		numberOfRecombParents = stoi(inputParams[5].c_str());

		auto numParams = (unsigned)searchSpace.size() / 2;
		tau0 = 1.0 / sqrt(2.0 * numParams);
		tau1 = 1.0 / sqrt(2.0 * sqrt(numParams));

		return { searchSpace, maxFitCalls, isSigmaVector, sigmaInitial, tau0, tau1, numberOfRecombParents };
	}

	auto ESsettingsFileInteractor::DisplayESConstants(const ParamsES& params) -> void
	{
		ClearConsoleWindow();
		printf("The optimizer will be launched with the following parameters:\n");
		printf("Search space:");
		for_each(begin(params.SeachSpace), end(params.SeachSpace), [](double value) {printf("%.1f ", value); });
		printf("\nMaximum number of fitness calls: %d\n", params.MaxFitCalls);
		printf("Is sigma vector: %s\n", params.IsSigmaVector ? "true" : "false");
		printf("Maximum initial sigma: %.2f\n", params.SigmaInitialMax);
		printf("Number of coupling parents: %d\n", params.NumberOfRecombParents);
	}
}