#ifndef CITY_HPP
#define CITY_HPP
#include <queue>
#include <vector>
#include "linq.hpp"
#include "base.hpp"
#include "cityconnection.hpp"
#include <map>
// This file containts of three classes, namely
//  1. City
//  2. CityConnection
//  3. Map 
// which are used to model the game board (Map) of our game.
// You can read a map from file in the following format 
// 
// <number of cities (n)>
// <city name 0>
// <city name 1>
//     ...
// <city name n-1
// <first endpoint 0> <second endpoint 0> <type 0>
// <first endpoint 1> <second endpoint 1> <type 1>
//     ...
// <first endpoint m-1> <second endpoint m-1> <type m-1>
//
// endpoints are determined by their id, i.e. the order they are read (starting with 0).
// The following connection types are supportet 
//
// - b (bus)
// - t (train)
// - a (airplane)

namespace ScotlandYard
{
	// class City 
	// Represents a city of the map, containing 
	//   - id, 
	//   - name
	//   - list of connections to other cities
	//   - referance to corresponding map
	class City
	{
		friend class ScotlandYard::Map;
	public:

		// Define Construtor explicit to avoid copying of cities
		explicit City(CityId id_, std::string const & name_, Map const & map_);

		// Returns the number of city connections i.e. the number of neighbour cities
		ConnectionId num_city_connections() const;

		// Return city connection 
		CityConnection const & city_connection(ConnectionId neighbor_id) const;

		Queryable<CityConnection> city_connections() const;
		// Getter for id
		CityId id() const;

		// Getter for name()
		std::string const & name() const;

		bool operator==(City second);
		bool operator==(City const second) const;
	private:

		// Add new CityConnection by id
		void add_connection(ConnectionId id);

		//////////////
		// Member 
		CityId const               _id;
		std::string const          _name;
		Map const &                _map;
		std::vector<ConnectionId>  _connections;
	};
}
#endif // !CITY_HPP
