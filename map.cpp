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
	/// class Map
	City & Map::city(CityId id)
	{
		assert(id < num_cities());
		return _cities[id.to_base_type()];
	}

	City const & Map::city(CityId const id) const
	{
		assert(id < num_cities());
		return _cities[id.to_base_type()];
	}

	CityConnection const & Map::connection(ConnectionId id) const
	{
		//println("Map connection: " << id);
		assert(id < num_city_connections());
		return _connections[id.to_base_type()];
	}

	CityId Map::num_cities() const
	{
		return CityId(_cities.Count());
	}

	ConnectionId Map::num_city_connections() const
	{
		return ConnectionId(_connections.Count());
	}

	CityId Map::add_new_city(std::string const & name)
	{
		CityId const new_id = num_cities();
		_cities.Add(City(new_id, name, *this));
		return new_id;
	}

	ConnectionId Map::add_new_connection(CityId ep1, CityId ep2, CityConnection::Type type)
	{
		ConnectionId const new_id = num_city_connections();
		_connections.Add(CityConnection(new_id, ep1, ep2, type, *this));
		city(ep1).add_connection(new_id);
		city(ep2).add_connection(new_id);
		return new_id;
	}

	Map::Map()
		:
		_cities(),
		_connections()
	{}

	Map::Map(std::string const & filename)
		:
		_cities(),
		_connections()
	{
		read_from_file(filename);
	}

	void Map::read_from_file(std::string const & filename)
	{
		assert(_cities.Count() == 0 and _connections.Count() == 0);
		std::ifstream infile(filename);
		std::string line;
		// Read number of cities
		size_t num_cities;
		{
			std::getline(infile, line);
			std::istringstream iss(line);
			iss >> num_cities;
			assert(!iss.fail());
		}

		// Read cities 
		for (size_t i = 0; i < num_cities; ++i)
		{
			std::getline(infile, line);
			std::istringstream iss(line);
			std::string name;
			iss >> name;
			assert(!iss.fail());
			add_new_city(name);
		}
		// Read city connections
		while (std::getline(infile, line))
		{
			size_t a, b;
			char t;
			std::istringstream iss(line);
			iss >> a >> b >> t;
			assert(!iss.fail());
			switch (t)
			{
			case 'b': add_new_connection(CityId(a), CityId(b), CityConnection::Type::bus); break;
			case 't': add_new_connection(CityId(a), CityId(b), CityConnection::Type::train); break;
			case 'a': add_new_connection(CityId(a), CityId(b), CityConnection::Type::airplane); break;
			default: std::runtime_error("input format broken");
			}
		}
	}
} // namespace ScotlandYard
