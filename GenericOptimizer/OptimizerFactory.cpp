#include "GenericOptimizer\OptimizerFactory.h"

using namespace std;
using namespace Evolutionary;
using namespace GenerationBased;
using namespace Parallel;

namespace GenericOptimizer
{
	auto OptimizerFactory::GenerateOptimizationEngine() -> shared_ptr<Optimizer>
	{
		printf("Welcome to the evolutionary optimizer\n\n");
		string filePath = boost::filesystem::current_path().string() + "\\OptSetting.txt"; // file to read/write
		auto isCorrectlyEnteredlNumber = false;

		int optimizerType;
		function<shared_ptr<Optimizer>(string)> engineCreationDelegate;

		do
		{
			printf("Select the optimizer type:\n0 - Generation Based Evolutionary Strategy \n"
				"1 - Parallel Evolutionary Strategy\nYour choice: ");
			cin >> optimizerType;

			switch (optimizerType)
			{
			case 0: // ESGB
				isCorrectlyEnteredlNumber = true;
				EngineGeneratorESGB::WriteESGBsampleSettingToFile(filePath);
				engineCreationDelegate = EngineGeneratorESGB::GenerateESGBEngine;
				break;
			case 1: // ESP
				isCorrectlyEnteredlNumber = true;
				EngineGeneratorESP::WriteESPsampleSettingToFile(filePath);
				engineCreationDelegate = EngineGeneratorESP::GenerateESPEngine;
				break;
			default:
				printf("\nWrong number! Please try again...\n");
			}
		} while (!isCorrectlyEnteredlNumber);

		printf("The settings file is generated in:\n\%s \n\nPlease modify it and press Enter\n", filePath.c_str());
		_getch(); // wait for the keypress to proceed

		// invoke delegate, which returns shared_ptr<Optimizer> and move the result
		return move(engineCreationDelegate(filePath));
	}

}