#include "map.hpp"
#include <cassert>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <ciso646>
#include <map>

namespace ScotlandYard
{
	//////////////////////////////////////
	/// class CityConnection

	City & CityConnection::city1()
	{
		return _map.city(_ep1);
	}

	City & CityConnection::city2()
	{
		return _map.city(_ep2);
	}

	City & CityConnection::other_city(City city)
	{
		assert(city.id() == _ep1 or city.id() == _ep2);
		if (city.id() == _ep1)
		{
			return city2();
		}
		else
		{
			return city1();
		}
	}

	City & CityConnection::other_city(CityId city)
	{
		assert(city == _ep1 or city == _ep2);
		if (city == _ep1)
		{
			return city2();
		}
		else
		{
			return city1();
		}
	}

	CityConnection::Type CityConnection::type() const
	{
		return _type;
	}

	CityConnection::CityConnection(ConnectionId id_, CityId ep1_, CityId ep2_, Type type_, Map & map_)
		:
		_id(id_),
		_ep1(ep1_),
		_ep2(ep2_),
		_type(type_),
		_map(map_)
	{
		assert(_ep1 < _map.num_cities() and _ep2 < _map.num_cities());
	}

	bool CityConnection::operator==(CityConnection second)
	{
		return (this->_ep1 == second.city1().id() && this->_ep2 == second.city2().id() && this->type() == second.type());
	}
}