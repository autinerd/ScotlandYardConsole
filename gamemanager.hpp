#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
#include "map.hpp"
#include "pairwisedistance.hpp"
#include "player.hpp"
#include <vector>

namespace ScotlandYard
{

	class GameManager
	{
	public:
		// Create player, load map and start game by calling private function play_game()
		GameManager(size_t num_player, std::string map_filename, size_t num_rounds = 20);
	private:
		// main loop
		void play_game();
		int do_round();
		bool CityContainsPlayer(CityId city);

		Map _map;
		PairwiseDistance const _dists;
		Queryable<HumanPlayer> _players;
		size_t _round;
		size_t _maxrounds;
		MisterX _misterX;

	};

} // namespace ScotlandYard 
#endif //GAMEMANAGER_HPP
