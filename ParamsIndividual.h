#pragma once
#include <vector>

namespace Evolutionary
{
	// class storing an individual, which is characterized by {vec(parameters),vec(sigma)} 
	class ParamsIndividual
	{
	private:
		using vecDouble = std::vector<double>;
		vecDouble _params;
		vecDouble _sigmas;
	public:

		ParamsIndividual(const vecDouble& param, const vecDouble& sigma) :
			_params{ param }, _sigmas{ sigma } {};

		ParamsIndividual(vecDouble&& param, vecDouble&& sigma) :
			_params{ move(param) }, _sigmas{ move(sigma) } {};

		ParamsIndividual(const ParamsIndividual& ind) :
			_params{ ind._params }, _sigmas{ ind._sigmas } {};

		explicit ParamsIndividual() = default;

		auto operator=(ParamsIndividual&& obj)->ParamsIndividual&
		{
			if (&obj == this)
			{
				return *this;
			}
			this->_params = move(obj._params);
			this->_sigmas = move(obj._sigmas);
			return *this;
		}

		auto operator=(const ParamsIndividual& second)->ParamsIndividual = delete;

		auto operator==(const ParamsIndividual& second)->bool
		{
			return _params == second._params &&  _sigmas == second._sigmas;
		}

		auto GetParamsSize() const->unsigned
		{
			return _params.size();
		}

		auto GetParamsRef() const->const vecDouble&
		{
			return _params;
		}

		auto CopyParams() const->vecDouble
		{
			return _params;
		}

		auto SetParams(const vecDouble& v)->void
		{
			_params = v;
		}

		auto GetSigmasSize() const->unsigned
		{
			return _sigmas.size();
		}

		auto GetSigmasRef() const->const vecDouble&
		{
			return _sigmas;
		}

		auto CopySigmas() const->vecDouble
		{
			return _sigmas;
		}

		auto SetSimgas(const vecDouble& v)->void
		{
			_sigmas = v;
		}
	};
}