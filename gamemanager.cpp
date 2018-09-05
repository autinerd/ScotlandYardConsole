#include "gamemanager.hpp"
#include "player.hpp"
#include "base.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#define println(x) std::cout << x << std::endl
namespace ScotlandYard
{
	GameManager::GameManager(size_t num_player, std::string map_filename, size_t num_rounds) : _map(map_filename), _dists(_map), _maxrounds(num_rounds), _misterX(_map)
	{
		srand((unsigned int)time(0));
		// Initialize random positions for players
		for (size_t i = 0; i < num_player; i++)
		{
			std::string name;
			std::cout << "Geben Sie den Namen fuer Spieler " << i + 1 << " ein: ";
			std::cin >> name;
			_players.Add(HumanPlayer(_map, name));
			CityId c = CityId(rand() % _map.num_cities().to_base_type());
			while (CityContainsPlayer(c))
			{
				c = CityId(rand() % _map.num_cities().to_base_type());
			}
			_players[i].InitPosition(c);
		}

		CityId c = CityId(rand() % _map.num_cities().to_base_type());
		while (CityContainsPlayer(c))
		{
			c = CityId(rand() % _map.num_cities().to_base_type());
		}
		_misterX.InitPosition(c);

		_round = 1;
		play_game();
	}

	void GameManager::play_game()
	{
		while (_round <= _maxrounds)
		{
			if (do_round() == 1)
			{
				return;
			}
			_round++;
		}
		println("Ihr habt es nicht geschafft, Mister X in der Zeit zu fangen. Er hat gewonnen!");
		return;
	}

	int GameManager::do_round()
	{
		println("");
		println("Runde: " << _round);
		println("");
		for (size_t i = 0; i < _players.Count(); i++)
		{
			HumanPlayer player = _players[i];
			println("");
			println("Entfernung Mister X zu Spieler " << player.name() << ": " << _dists.dist(player.pos(), _misterX.pos()));
			player.move();
			println("Aktuelle Position: " << _map.city(player.pos()).name());
			if (_dists.dist(player.pos(), _misterX.pos()) == 0)
			{
				println("Ihr habt Mister X gefasst, herzlichen Glueckwunsch!");
				return 1;
			}
			_players[i] = player;
		}
		_misterX.moveMisterX(_players);
		return 0;
	}

	bool GameManager::CityContainsPlayer(CityId city)
	{
		return _players.Any([city](HumanPlayer p) {return p.pos() == city; }) || _misterX.pos() == city;
	}
}