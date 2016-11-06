#include "Precompiled.h"

using namespace std;
using namespace HelperFunctions;
using namespace GenericOptimizer;
using namespace Evolutionary;
using namespace Randomness;
using namespace BioMechanisms;
using namespace GenerationBased;
using namespace Parallel;

auto main()->int
{
	// Test linear mapping function
	{
		auto values = vector<double>{ 0.0, 0.5, 1.0, 0.6, };
		auto intervalsFrom = make_pair(0, 1);
		auto intervalsTo = vector<pair<double, double>>{ make_pair(-1.2, 2.8), make_pair(2.2, 4.8), make_pair(3.0, 4.0),make_pair(-2.4,3.4) };

		auto results = MapLinearlyToInterval(values, intervalsFrom, intervalsTo);

		try
		{
			results = MapLinearlyToInterval(values, intervalsFrom, intervalsTo);
			ASSERT(results[0] = -1.2);
			ASSERT(results[1] = 3.5);
			ASSERT(results[2] = 4.0);
			ASSERT(results[3] = 1.08);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	// Test fitness function class
	{
		auto fit = FitnessFromMathExpression{};
		auto v = vector<double>{ 0.1,0.2,0.3 };
		auto result = fit.EvaluateFitness(&v[0],v.size());
	}

	// Test ParamsES
	{
		auto searchSpace = vector<double>{ -1.0, 2.0, -3.4, 5.2 };
		unsigned maxFitCalls = 1500;
		bool isSigmaVector = true;
		double sigmaInitial = 0.35;
		unsigned NumberOfRecombParents = 3;
		double tau0 = 0.125;
		double tau1 = 0.32;
		ParamsES constsES{ searchSpace,maxFitCalls, isSigmaVector, sigmaInitial, tau0, tau1,NumberOfRecombParents };
	}

	// test ParamsIndividual class
	{
		auto p1 = vector<double>{ 0.1, 0.5, 0.7 };
		auto s1 = vector<double>{ 0.11, 0.12, 0.12 };

		ParamsIndividual ind1{ move(p1), move(s1) };// move constructor
		ASSERT(ind1.GetParamsSize() == 3);
		ParamsIndividual ind2{ { 0.122, 0.52, 0.72 },{ 0.111, 0.122, 0.123 } }; // move constructor
		ASSERT(!(ind1 == ind2));
		ParamsIndividual ind3{ { 0.1, 0.5, 0.7 },{ 0.11, 0.12, 0.12 } };// move constructor
		ASSERT((ind1 == ind3));
		ind3 = move(ind2); // move assignment
		ind3 = move(ind3); // move assignment
		ASSERT(ind2.GetParamsRef().empty());
		ASSERT(ind2.GetParamsRef().empty());
		vector<double> p{ 0.122, 0.52, 0.72 };
		ASSERT(ind3.GetParamsRef() == p);
		vector<double> s{ 0.111, 0.122, 0.123 };
		ASSERT(ind3.GetSigmasRef() == s);
		auto& params1=ind3.GetParamsRef();
		auto& params2 = ind3.GetParamsRef();
		ASSERT(&params1 == &params2);
		auto params3 = ind3.CopyParams();
		ASSERT(&params3 != &params2);
		auto& sigmas1 = ind3.GetSigmasRef();
		auto& sigmas2 = ind3.GetSigmasRef();
		ASSERT(&sigmas1 == &sigmas2);
		auto simgas3 = ind3.CopySigmas();
		ASSERT(&simgas3 != &sigmas1);
	}

	// test class SortedFitnessTable
	{
		unsigned maxSize = 5;
		auto sortedMap = Evolutionary::SortedFitnessTable{ maxSize };
		bool isAdded;
		double fit1 = 10.2;
		double fit2 = -5.3;
		double fit3 = 21.1;
		double fit4 = 21.1;
		double fit5 = 35.2;
		double fit6 = -35.2;
		double fit7 = 35.2;

		Evolutionary::ParamsIndividual par1{ { -4.3, 5.1, 4.6 },{ 0.23, 0.34, 0.12 } };
		Evolutionary::ParamsIndividual par2{ { -5.3, 6.1, 1.6 },{ 1.23, 1.34, 1.12 } };
		Evolutionary::ParamsIndividual par3{ { -6.3, 7.1, 4.6 },{ 2.23, 2.34, 2.12 } };
		Evolutionary::ParamsIndividual par4{ { -7.3, 8.1, 4.6 },{ 3.23, 3.34, 3.12 } };
		Evolutionary::ParamsIndividual par5{ { -8.3, 9.1, 4.6 },{ 3.23, 4.34, 4.12 } };
		Evolutionary::ParamsIndividual par6{ { -9.3, 10.1, 4.6 },{ 4.23, 5.34, 5.12 } };
		Evolutionary::ParamsIndividual par7{ { -10.3, 11.1, 4.6 },{ 5.23, 6.34, 6.12 } };

		isAdded = sortedMap.AddItem(fit1, par1);
		ASSERT(isAdded == true);
		ASSERT(sortedMap[0].first == 10.2);
		isAdded = sortedMap.AddItem(fit2, par2);
		ASSERT(isAdded == true);
		ASSERT(sortedMap[1].first == -5.3);
		isAdded = sortedMap.AddItem(fit3, par3);
		ASSERT(isAdded == true);
		isAdded = sortedMap.AddItem(fit4, par4);
		ASSERT(isAdded == true);
		isAdded = sortedMap.AddItem(fit5, par5);
		ASSERT(isAdded == true);
		isAdded = sortedMap.AddItem(fit6, par6);
		ASSERT(isAdded == false);
		isAdded = sortedMap.AddItem(fit7, par7);
		ASSERT(isAdded == true);

		ASSERT(par1 == sortedMap[4].second);
		ASSERT(par3 == sortedMap[2].second);

		auto v = sortedMap[3];
	}

	// test random MersenneTwisterInt
	{
		double average = 0.0;
		int minn = -2;
		int maxx = 5;
		const int steps = 8;
		int p[steps] = {};
		auto instMT = MersenneTwisterInt(minn, maxx, 5489u);
		auto n1 = instMT.NextRand();
		unsigned N = 10000;
		for (unsigned i = 0; i < N; i++)
		{
			n1 = instMT.NextRand();
			average += n1;
			ASSERT(n1 <= maxx);
			ASSERT(n1 >= minn);
			++p[n1 + 2];
		}
		for (int i = minn; i <= maxx; i++)
		{
			printf("%d occured %d time\n", i, p[i + 2]);
		}
		printf("Average between %d and %d in a set of %d points is %f\n", minn, maxx, N, average / N);
	}

	// test random MersenneTwisterUniformDouble
	{
		printf("\nnew random test\n");
		double average = 0.0;
		double minn = -1.2;
		double maxx = 5.3;
		auto instMT = Randomness::MersenneTwisterUniformDouble(minn, maxx, 5489u);
		auto n1 = instMT.NextRand();
		unsigned N = 10000;
		for (unsigned i = 0; i < N; i++)
		{
			n1 = instMT.NextRand();
			average += n1;
			ASSERT(n1 <= maxx);
			ASSERT(n1 >= minn);
			//printf("%f\n", n1);
		}
		printf("Average between %f and %f in a set of %d points is %f\n", minn, maxx, N, average / N);
	}

	// test random MersenneTwisterSTDNorm
	{
		printf("std norm random test\n");
		const int nstars = 150;    // maximum number of stars to distribute
		const int steps = 11;
		int p[steps] = {};
		auto instMT = Randomness::MersenneTwisterStdNorm(5489u);
		auto n1 = instMT.NextRand();
		unsigned N = 1000000;
		for (unsigned i = 0; i < N; i++)
		{
			n1 = instMT.NextRand();
			if ((n1 > -5.0) && (n1 < 5.0)) ++p[(int)round(n1) + 5];
		}
		for (int i = 0; i < steps; ++i)
		{
			cout << string(p[i] * nstars / N, '*').c_str() << endl;
		}
	}

	// test class StandardMutation
	{
		printf("Test mutation\n");
		unsigned numParams = 4;
		double tau0 = 1.0 / sqrt(2.0 * numParams);
		double tau1 = 1.0 / sqrt(2.0 * sqrt(numParams));
		auto instMT = make_shared<Randomness::MersenneTwisterStdNorm>(5489u);
		Evolutionary::BioMechanisms::StandardMutation instR{ instMT, tau0, tau1 };

		Evolutionary::ParamsIndividual par11{ { 0.1, 0.2, 0.3, 0.4 },{ 0.05, 0.1, 0.1, 0.08 } };
		Evolutionary::ParamsIndividual par22{ { 0.11, 0.22, 0.33, 0.44 },{ 0.2, 0.22, 0.222, 0.2222 } };
		Evolutionary::ParamsIndividual par33{ { 0.111, 0.222, 0.333, 0.444 },{ 0.2 } };
		Evolutionary::ParamsIndividual parException{ { 0.111, 0.222, 0.333, 0.444 },{ 0.2, 0.3 } };
		ASSERT(numParams == par11.GetParamsSize());
		ASSERT(numParams == par22.GetParamsSize());

		instR.Mutate(par11);
		instR.Mutate(par22);
		instR.Mutate(par33);

		try
		{
			instR.Mutate(parException);
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}


	// test Selection
	{
		printf("Test selection\n");
		int min = 0;
		int max = 5;
		unsigned seed_ = 5489u;
		unsigned parentsNumber = 2;
		shared_ptr<Randomness::IRandInt> instanceRandInt = make_shared<Randomness::MersenneTwisterInt>(min, max, seed_);
		auto instanceSelector = Evolutionary::BioMechanisms::UniqueParentsSelection(instanceRandInt, parentsNumber);

		auto isUnique = [](vector<unsigned> v)
		{
			sort(begin(v), end(v));
			for (size_t i = 0; i < v.size() - 1; i++)
			{
				if (v[i] == v[i + 1])
				{
					return false;
				}
			}
			return true;
		};

		unsigned restarts = 10000;
		auto parSelected = vector<unsigned>(max + 1);
		auto parents = instanceSelector.Select();
		for (unsigned i = 0; i < restarts; i++)
		{
			ASSERT(isUnique(parents) == true);
			parents = instanceSelector.Select();

			for_each(begin(parents), end(parents), [&parSelected](decltype(parents[0]) s)
			{
				//s++;
				parSelected[s]++;
			});
		}

		printf("Statistics of selection of parents from %d to %d in %d restarts\n", min, max, restarts);
		for (size_t i = 0; i < parSelected.size(); i++)
		{
			printf("Parent %d selected %d times\n", i, parSelected[i]);
		}
	}

	//test Recombination
	{
		double min = 0.0;
		double max = 1.0;
		unsigned _seed = 5489u;
		shared_ptr<IRandDouble> instRandInt = make_shared<MersenneTwisterUniformDouble>(min, max, _seed);
		auto instR =ProbabilisticRecombination{ instRandInt };
		auto par1 = ParamsIndividual{ { -4.3, 5.1, 1.6 },{ 0.1, 0.11, 0.111 } };
		auto par2 = ParamsIndividual{ { -5.3, 6.1, 2.6 },{ 0.2, 0.22, 0.222 } };
		auto par3 = ParamsIndividual{ { -6.3, 7.1, 3.6 },{ 0.3, 0.33, 0.333 } };
		vector<ParamsIndividual> indivSet{ par1, par2, par3 };

		auto recombined = instR.Recombine(indivSet);
		ASSERT(round(1000 * recombined.GetSigmasRef().at(0)) / 1000 == 0.2);
		ASSERT(round(1000 * recombined.GetSigmasRef().at(1)) / 1000 == 0.22);
		ASSERT(round(1000 * recombined.GetSigmasRef().at(2)) / 1000 == 0.222);

		auto par11 =ParamsIndividual{ { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6,1.7,1.8,1.9,1.11,1.12,1.13,1.14 },{ 0.1, 0.11, 0.111, 0.1111 } };
		auto par22 = ParamsIndividual{ { 2.1, 2.2, 2.3, 2.4, 2.5, 2.6,2.7,2.8,2.9,2.11,2.12,2.13,2.14 },{ 0.2, 0.22, 0.222, 0.2222 } };
		vector<ParamsIndividual> indivSet2{ par11, par22 };
		recombined = instR.Recombine(indivSet2);

		ASSERT(round(1000 * recombined.GetSigmasRef().at(0)) / 1000 == 0.15);
		ASSERT(round(1000 * recombined.GetSigmasRef().at(1)) / 1000 == 0.165);
		ASSERT(round(10000 * recombined.GetSigmasRef().at(2)) / 10000 == 0.1665);
		ASSERT(round(100000 * recombined.GetSigmasRef().at(3)) / 100000 == 0.16665);
	}
	// test OptimizerESGB (generation based evolutionary strategy)
	{
		cout << "Main thread id: " << this_thread::get_id() << endl;
		printf("\nTesting generation-based version ...\n");
		bool isSigmaVector = true;
		unsigned parents = 7;
		unsigned recombParents = 2;
		initializer_list<double> searchSpace{ -8.3, 4.5, -2.3, 7.3, -1.5, 9.5 };
		unsigned numParams = (unsigned)searchSpace.size() / 2;
		double tau0 = 1.0 / sqrt(2.0 * numParams);
		double tau1 = 1.0 / sqrt(2.0 * sqrt(numParams));
		unsigned maxFitCalls = 2500;
		unsigned childrenNum = 30;
		double sigmaInitial = 0.3;
		unsigned numberOfRecombParents = 2;

		unsigned _seed = 5489u;
		// fitness table
		shared_ptr<ISortedFitnessTable> instTable = make_shared<SortedFitnessTable>(parents);
		// ES constants
		ParamsES constsES { searchSpace, maxFitCalls, isSigmaVector, sigmaInitial, tau0, tau1, numberOfRecombParents };
		// ESGB constants
		auto constsESGB = ParamsESGB{ parents, childrenNum };
		// random engine generating double in (0.0,1.0)
		shared_ptr<IRandDouble> instMtDouble = make_shared<Randomness::MersenneTwisterUniformDouble>(0.0, 1.0, _seed);
		// random engine generating integer in (0,parents - 1) range
		shared_ptr <IRandInt> instMtInt = make_shared<Randomness::MersenneTwisterInt>(0, parents - 1, _seed);
		// selection
		shared_ptr<ISelection> instSelection = make_shared<UniqueParentsSelection>(instMtInt, recombParents);
		// recombination
		shared_ptr<IRecombination> instRecomb = make_shared<ProbabilisticRecombination>(instMtDouble);
		// engine generating doubles according to StdNorm distribution
		shared_ptr<IRandDouble> instMtStdNorm = make_shared<MersenneTwisterStdNorm>(_seed);
		// mutation
		shared_ptr<IMutation> instMutation = make_shared<StandardMutation>(instMtStdNorm, tau0, tau1);

		shared_ptr<Optimizer> engineESGB = make_shared<OptimizerESGB>(instTable, constsES,
			constsESGB, instMtDouble, instSelection, instRecomb, instMutation);

		//shared_ptr<IFitness> instFit(new FitnessFromMathExpression{});
		shared_ptr<IFitness> instFit(GenerateFitnessObject());
		unsigned restarts = 6;
		for (unsigned i = 0; i < restarts; i++)
		{
			engineESGB->StartOptimization(instFit);
		}
	}

	// test OptimizerESP
	{
		printf("\nTesting parallel version ...\n");
		bool isSigmaVector = true;
		unsigned tableSize = 20;
		unsigned recombParents = 2;
		initializer_list<double> searchSpace{ -8.3, 4.5, -2.3, 7.3, -1.5, 9.5 };//{ -6.0, 3.0, -6.0, 3.0, -6.0, 3.0 };
		unsigned numParams = (unsigned)searchSpace.size() / 2;
		double tau0 = 1.0 / sqrt(2.0 * numParams);
		double tau1 = 1.0 / sqrt(2.0 * sqrt(numParams));
		unsigned maxFitCalls = 3000;
		double sigmaInitial = 0.3;
		unsigned _seed = 5489u;
		unsigned LogicalProcNum = thread::hardware_concurrency();

		// fitness table
		shared_ptr<ISortedFitnessTable> instTable = make_shared<SortedFitnessTable>(tableSize);
		// ES constants
		ParamsES constsES{ searchSpace,maxFitCalls, isSigmaVector, sigmaInitial, tau0, tau1,recombParents };
		// ESGB constants
		auto constsESP = ParamsESP{ tableSize, LogicalProcNum };
		// random engine generating double in (0.0,1.0)
		shared_ptr<IRandDouble> instMtDouble = make_shared<MersenneTwisterUniformDouble>(0.0, 1.0, _seed);
		// random engine generating integer in (0,parents - 1) range
		shared_ptr <IRandInt> instMtInt = make_shared<MersenneTwisterInt>(0, tableSize - 1, _seed);
		// selection
		shared_ptr<ISelection> instSelection = make_shared<UniqueParentsSelection>(instMtInt, recombParents);
		// recombination
		shared_ptr<IRecombination> instRecomb = make_shared<ProbabilisticRecombination>(instMtDouble);
		// engine generating doubles according to StdNorm distribution
		shared_ptr<IRandDouble> instMtStdNorm = make_shared<MersenneTwisterStdNorm>(_seed);
		// mutation
		shared_ptr<IMutation> instMutation = make_shared<StandardMutation>(instMtStdNorm, tau0, tau1);
		// ParallelES engine
		shared_ptr<Optimizer> engineESP = make_shared<OptimizerESP>(instTable, constsES, constsESP, instMtDouble,
			instSelection, instRecomb, instMutation);

		shared_ptr<IFitness> instFit (new FitnessFromMathExpression{});

		unsigned restarts = 6;
		for (unsigned i = 0; i < restarts; i++)
		{
			engineESP->StartOptimization(instFit);
		}
		printf("\nOptimization finished\n");
	}

	// test boost filesystem
	{
		std::string filePath = boost::filesystem::current_path().string() + "\\OptSetting.txt"; // file to read/write
	}

	printf("\nAll tests passed successfully\n");
	getch();

}