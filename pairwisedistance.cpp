#include "pairwisedistance.hpp"
#include "linq.hpp"
#include <queue>
namespace ScotlandYard
{
	PairwiseDistance::PairwiseDistance(Map & map_) : _map(map_)
	{
	}

	size_t PairwiseDistance::dist(CityId a, CityId b) const
	{
		if (a == b)
		{
			return 0;
		}
		size_t depth = 0;
		Queryable<KeyValuePair<size_t, Queryable<CityId>>> dict;
		dict.Add(KeyValuePair<size_t, Queryable<CityId>>(0, Queryable<CityId>()));
		dict[0].value.Add(a);
		while (depth <= 10)
		{
			depth++;
			dict.Add(KeyValuePair<size_t, Queryable<CityId>>(depth, Queryable<CityId>()));
			for (CityId id : dict[depth - 1].value.ToVector())
			{
				Queryable<CityId> qu = _map.city(id).city_connections().ConvertAll<CityId>([id](CityConnection c) {return c.other_city(id).id(); });
				for (CityId id2 : qu.ToVector())
				{
					dict[depth].value.Add(id2);
				}
				if (dict[depth].value.Any([b](CityId d) {return d == b; }))
				{
					return depth;
				}
			}
		}
		return SIZE_MAX;
	}
}