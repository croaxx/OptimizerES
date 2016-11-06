#include "Evolutionary\OptimizerES.h"

using namespace std;
using namespace Randomness;
using namespace HelperFunctions;

namespace Evolutionary
{

	OptimizerES::OptimizerES(shared_ptr<ISortedFitnessTable> fitnessTable, const ParamsES& constantsES):
		_fitnessTable{ fitnessTable }, _constantsES{ constantsES } {};

	auto OptimizerES::DisplayFitnessTable() const-> void
	{
		// Loop over all rows in the fitness table
		for (unsigned i = 0; i < _fitnessTable->TableSize(); i++)
		{
			printf("%.5e   ", _fitnessTable->operator[](i).first);

			auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are within  [0.0,1.0] interval
			vector<pair<double, double>> intervalsTo;
			
			for (unsigned j = 0; j < _constantsES.SeachSpace.size(); j += 2)
			{
				intervalsTo.push_back(make_pair(_constantsES.SeachSpace[j], _constantsES.SeachSpace[j + 1]));
			}

			auto mappedParams = MapLinearlyToInterval(_fitnessTable->operator[](i).second.GetParamsRef(), intervalsFrom, intervalsTo);

			for (unsigned j = 0; j < _constantsES.ParamsNumber; j++)
			{
				printf("%+.5f   ", mappedParams[j]);
			}

			auto const sigSize = _fitnessTable->operator[](i).second.GetSigmasSize();

			for (unsigned j = 0; j < sigSize; j++)
			{
				printf("%.4f   ", _fitnessTable->operator[](i).second.GetSigmasRef().at(j));
			}

			printf("\n");
		}
		printf("\n");
	}

	auto OptimizerES::GenRndParams(shared_ptr<IRandDouble> rnd) const -> decltype(declval<ParamsIndividual>().CopyParams())
	{
		decltype(declval<ParamsIndividual>().CopyParams()) params(_constantsES.ParamsNumber, 0.0);

		for_each(begin(params), end(params), [&](decltype(*begin(params)) x)
		{
			x = rnd->NextRand();
		});

		return move(params);
	}

	auto OptimizerES::GenInitialSigmas() const -> decltype(declval<ParamsIndividual>().CopySigmas())
	{
		decltype(declval<ParamsIndividual>().CopySigmas()) sigmas{ _constantsES.SigmaInitialMax };

		if (_constantsES.IsSigmaVector)
		{
			sigmas.resize(_constantsES.ParamsNumber, _constantsES.SigmaInitialMax);
		}

		return move(sigmas);
	}

	auto OptimizerES::ReadSavePath(const std::string& settingFilePath) -> std::string
	{
		string savePath;
		ifstream file(settingFilePath);
		if (!file.is_open()) throw exception("Could not open file for reading.");
		getline(file, savePath); // file path description
		getline(file, savePath);// file path

		file.close();

		return savePath;
	}

	auto OptimizerES::WriteFitnessTableToFile(ofstream& fileObject) const->void
	{
		// Loop over all rows in the fitness table
		for (unsigned i = 0; i < _fitnessTable -> TableSize(); i++)
		{
			fileObject << std::scientific << std::setprecision(5) << _fitnessTable -> operator[](i).first << "; ";

			auto intervalsFrom = make_pair<double, double>(0.0, 1.0); // parameter values in ES are within  [0.0,1.0] interval
			vector<pair<double, double>> intervalsTo;

			for (unsigned j = 0; j < _constantsES.SeachSpace.size(); j += 2)
			{
				intervalsTo.push_back(make_pair(_constantsES.SeachSpace[j], _constantsES.SeachSpace[j + 1]));
			}

			auto mappedParams = MapLinearlyToInterval(_fitnessTable -> operator[](i).second.GetParamsRef(), 
													  intervalsFrom,
													  intervalsTo);

			for (unsigned j = 0; j < _constantsES.ParamsNumber; j++)
			{
				fileObject << std::scientific << std::setprecision(5) << mappedParams[j] << " ";
			}

			fileObject << "; ";
			const auto sigSize = _fitnessTable -> operator[](i).second.GetSigmasSize();

			for (unsigned j = 0; j < sigSize; j++)
			{
				fileObject << std::scientific << std::setprecision(5) << _fitnessTable->operator[](i).second.GetSigmasRef().at(j) << " ";
			}

			fileObject << "\n";
		}
		fileObject << "\n";
	}


	auto OptimizerES::WriteFitnessEntryToFile(ofstream& fileObject, const double& fitness,
											  const vector<double>& mappedPrams,
											  const std::vector<double>& sigmas) const->void
	{
		fileObject << std::scientific << std::setprecision(5) << fitness << "; ";

		for (const auto& e : mappedPrams)
		{
			fileObject << std::scientific << std::setprecision(5) << e << " ";
		}

		fileObject << "; ";

		for (const auto& e : sigmas)
		{
			fileObject << std::scientific << std::setprecision(5) << e << " ";
		}

		fileObject << "\n";
	}

}