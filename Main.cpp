#include "Precompiled.h"

using namespace std;
using namespace GenericOptimizer;
using namespace chrono;

auto main()->int
{
	shared_ptr<IFitness> fitnessObject(GenerateFitnessObject()); // fitness evaluation is implemented in an external .dll

	auto engine = OptimizerFactory::GenerateOptimizationEngine();

	printf("\nEnter the number of optimization restarts: ");
	unsigned restarts;
	cin >> restarts;

	vector<double> bestFitnesses(restarts);

	auto start_t = high_resolution_clock::now();
	for (unsigned i = 0; i < restarts; i++)
	{
		auto result = engine->StartOptimization(fitnessObject);
		if (!result->IsEmpty()) bestFitnesses[i] = (*result)[0].first;
	}
	auto end_t = high_resolution_clock::now();

	auto averageFit = accumulate(begin(bestFitnesses), end(bestFitnesses), 0.0) / restarts;
	printf("Number of optimization restarts performed: %d\n", restarts);
	printf("Best fitness found: %f\n", *max_element(begin(bestFitnesses), end(bestFitnesses)));
	printf("Average fitness is: %f\n", averageFit);
	printf("Elapsed time is:  %d hrs: ", duration_cast<hours>(end_t - start_t).count());
	printf("%d min:  ", duration_cast<minutes>(end_t - start_t).count() % 60);
	printf("%d sec:  ", duration_cast<seconds>(end_t - start_t).count() % 60);
	printf("%d ms\n", duration_cast<milliseconds>(end_t - start_t).count() % 1000);
	getch();
}