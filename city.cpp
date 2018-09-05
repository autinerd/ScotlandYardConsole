#include "map.hpp"
#include "linq.hpp"
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
	/// class City
	ConnectionId City::num_city_connections() const
	{
		return ConnectionId(_connections.size());
	}

	CityConnection const & City::city_connection(ConnectionId neighbor_id) const
	{
		//println("CityConnection: " << neighbor_id.to_base_type());
		assert(_connections[neighbor_id.to_base_type()] < _map.num_city_connections());
		return _map.connection(_connections[neighbor_id.to_base_type()]);
	}

	Queryable<CityConnection> City::city_connections() const
	{
		int index = 0;
		return Queryable<ConnectionId>(_connections).ConvertAll<CityConnection>([this, &index](ConnectionId i) { i++; return CityConnection(this->city_connection(ConnectionId(index++))); });
	}

	CityId City::id() const
	{
		return _id;
	}

	std::string const & City::name() const
	{
		return _name;
	}

	bool City::operator==(City second) const
	{
		return this->id() == second.id();
	}

	City::City(CityId id_, std::string const & name_, Map const & map_)
		:
		_id(id_),
		_name(name_),
		_map(map_),
		_connections()
	{}

	void City::add_connection(ConnectionId id)
	{
		_connections.push_back(id);
	}
}