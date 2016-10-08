#include "Precompiled.h"

using namespace std;
using namespace GenericOptimizer;

auto main()->int
{
	auto fitnessObject = FitnessFromMathExpression{}; // this class is to be modified for each optimization

	auto engine = OptimizerFactory::GenerateOptimizationEngine();

	printf("\nEnter the number of optimization restarts: ");
	unsigned restarts;
	cin >> restarts;

	vector<double> bestFitnesses(restarts);

	auto start_t = chrono::high_resolution_clock::now();
	for (unsigned i = 0; i < restarts; i++)
	{
		auto result = engine->StartOptimization(fitnessObject);
		if (!result->IsEmpty()) bestFitnesses[i] = (*result)[0].first;
	}
	auto end_t = chrono::high_resolution_clock::now();

	auto averageFit = accumulate(begin(bestFitnesses), end(bestFitnesses), 0.0) / restarts;
	printf("Number of optimization restarts performed: %d\n", restarts);
	printf("Best fitness found: %f\n", *max_element(begin(bestFitnesses), end(bestFitnesses)));
	printf("Average fitness is: %f\n", averageFit);
	printf("Elapsed time is:  %d hrs: ", chrono::duration_cast<chrono::hours>(end_t - start_t).count());
	printf("%d min:  ", chrono::duration_cast<chrono::minutes>(end_t - start_t).count() % 60);
	printf("%d sec:  ", chrono::duration_cast<chrono::seconds>(end_t - start_t).count() % 60);
	printf("%d ms\n", chrono::duration_cast<chrono::milliseconds>(end_t - start_t).count() % 1000);
	getch();
}