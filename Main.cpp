#include "Precompiled.h"

using namespace std;
using namespace GenericOptimizer;
using namespace chrono;

auto main() -> int
{
	shared_ptr<IFitness> fitnessObject { GenerateFitnessObject() }; // fitness evaluation is implemented in an external .dll

	shared_ptr<Optimizer> engine = OptimizerFactory::GenerateOptimizationEngine(); // user sets optimization engine

	printf("\nEnter the number of optimization restarts: "); // get the input from user
	unsigned restarts;
	cin >> restarts;

	vector<double> bestFitnesses(restarts);

	auto start_t = high_resolution_clock::now(); // start time measurement

	for (unsigned i = 0; i < restarts; i++)
	{
		auto result = engine -> StartOptimization(fitnessObject);
		if (!result -> IsEmpty()) bestFitnesses[i] = (*result)[0].first;
	}

	auto end_t = high_resolution_clock::now(); // finish time measurement

	// Generic optimization output
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