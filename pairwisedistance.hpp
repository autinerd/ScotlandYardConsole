#ifndef PAIRWISEDISTANCE_HPP
#define PAIRWISEDISTANCE_HPP
#include "map.hpp"
namespace ScotlandYard
{

	class PairwiseDistance
	{
	public:
		PairwiseDistance(Map & map_);

		// Returns the distance between a and b, i.e. the minimum number of CityConnections
		// we need to travel from a to b (or vice versa);
		size_t dist(CityId a, CityId b) const;
		
	private:
		Map const & _map;
	};

} //namespace ScotlandYard
#endif // PAIRWISEDISTANCE_HPP
