#pragma once

namespace Evolutionary
{
	// This class holds parameters, required for evolutionary strategy optimization
	class ParamsES
	{
	public:
		const std::vector<double> SeachSpace;
		const unsigned MaxFitCalls;
		const bool IsSigmaVector;
		const double SigmaInitialMax;
		const unsigned NumberOfRecombParents;
		const double Tau0;
		const double Tau1;
		const unsigned ParamsNumber;

		ParamsES(const std::vector<double> seachSpace, const unsigned maxFitCalls,
			const bool isSigmaVector, const double sigmaInitial, const double tau0, const double tau1, const unsigned numberOfRecombParents) :
			SeachSpace{ seachSpace }, MaxFitCalls{ maxFitCalls }, IsSigmaVector{ isSigmaVector },
			SigmaInitialMax{ sigmaInitial }, Tau0{ tau0 }, Tau1{ tau1 }, ParamsNumber{ (unsigned)seachSpace.size() / 2 },
			NumberOfRecombParents{ numberOfRecombParents } {}

		ParamsES() = delete;
		//ParamsES(ParamsES&&) = delete;
		auto operator=(const ParamsES & obj)->ParamsES & = delete;
		//auto operator=(ParamsES&& obj)->ParamsES & = delete;
	};
}

