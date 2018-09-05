#ifndef DHBW_MAP_HPP
#define DHBW_MAP_HPP
#include <queue>
#include <vector>
#include "base.hpp"
#include "linq.hpp"
#include "city.hpp"
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
// The following connection types are supported 
//
// - b (bus)
// - t (train)
// - a (airplane)

namespace ScotlandYard
{
	// Class Map
	class Map
	{
	public:
		// C'tor for empty Map
		Map();

		// Construct map by file
		Map(std::string const & filename);

		// returns City by id
		City & city(CityId id);
		City const & city(CityId id) const;
		// returns CityConnection by id
		CityConnection const & connection(ConnectionId id) const;
		// returns number of cities
		CityId num_cities() const;
		// returns number of city connections
		ConnectionId num_city_connections() const;
		// add new city
		// returns the id of the new city
		CityId add_new_city(std::string const & name);
		// add new city connection
		// returns the id of the new connection
		ConnectionId add_new_connection(CityId ep1, CityId ep2, CityConnection::Type type);
		// debug method
		void print(std::ostream & out = std::cout);
	private:
		// Read input file and create cities and connections
		void read_from_file(std::string const & filename);

		// Returns true if and only if the Map is connected, i.e. there is a path 
		// from every city to every other city.

		Queryable<City>				_cities;
		Queryable<CityConnection>	_connections;

	};
} //namespace ScotlandYard
#endif //DHBW_MAP_HPP