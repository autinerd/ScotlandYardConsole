#ifndef BASE_HPP
#define BASE_HPP
#include "strong_typedefs.hpp"
#define println(x) std::cout << x << std::endl
// This file containts basic typedefs and forward declarations for this project


namespace ScotlandYard 
{

// Strong index typedefs
STRONG_INDEX_TYPEDEF(CityId,size_t);
STRONG_INDEX_TYPEDEF(ConnectionId,size_t);
STRONG_INDEX_TYPEDEF(PlayerId,size_t);
	
} // namespace ScotlandYard
#endif //BASE_HPP
