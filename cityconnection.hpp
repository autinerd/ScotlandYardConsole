#ifndef CITYCONNECTION_HPP
#define CITYCONNECTION_HPP
#include <queue>
#include <vector>
#include "base.hpp"
#include <map>

namespace ScotlandYard
{
	class Map;
	class City;
	// Class representing the connection between two cities
	class CityConnection
	{
		friend class ScotlandYard::Map;
	public:
		
		// Enum representing the Type of this Connection
		enum class Type { bus, train, airplane };

		// C'tor
		explicit CityConnection(ConnectionId id_, CityId ep1_, CityId ep2_, Type type_, Map & map_);

		City & city1();
		City & city2();
		// returns the endpoint which is not city
		City & other_city(City city);
		City & other_city(CityId city);
		Type type() const;
		bool operator==(CityConnection second);
	private:
		//////////////
		// Member 
		ConnectionId _id;
		CityId const _ep1;
		CityId const _ep2;
		Type const   _type;
		Map &  _map;

	};
}

#endif // !CITYCONNECTION_HPP
