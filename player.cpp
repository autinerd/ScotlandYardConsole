#include "player.hpp"
#include <random>
#include <time.h>
#include <vector>
#include <map>
#include <random>
#include <time.h>
namespace ScotlandYard
{
	/// Player
	Player::Player(Map map_, std::string name_) : _name(name_), _pos(255), _map(map_)
	{
	}

	std::string const & Player::name() const
	{
		return _name;
	}

	/// HumanPlayer

	void HumanPlayer::move()
	{
		println("");
		println("Spieler " << _name << " in " << _map.city(_pos).name());
		println("");
		int i = -1;
		for (CityConnection cc : _map.city(_pos).city_connections().ToVector())
		{
			i++;
			std::string type;
			switch (cc.type())
			{
			case CityConnection::Type::airplane:
				type = "airplane";
				break;
			case CityConnection::Type::bus:
				type = "bus";
				break;
			case CityConnection::Type::train:
				type = "train";
			default:
				break;
			}
			println(i << ": " << type << ": " << _map.city(_pos).name() << " - " << cc.other_city(_pos).name());
		}
		int answer = -1;
		do
		{
			std::cout << "Auswahl: ";
			std::cin >> answer;
		} while (answer > i || answer < 0);
		println("Bewegen von " << _map.city(_pos).name() << " nach " << _map.city(_pos).city_connections()[answer].other_city(_pos).name());
		_pos = _map.city(_pos).city_connections()[answer].other_city(_pos).id();
	}

	MisterX::MisterX(Map map_) : Player::Player(map_, "Mister X")
	{
		srand((unsigned int)time(0));
	}

	void MisterX::move()
	{
	}

	/// Mister X
	void MisterX::moveMisterX(Queryable<HumanPlayer> const & q)
	{
		println("");
		println("Mister X ist am Zug...");
		int j = -1;
		bool empty = false;
		for (size_t i = 0; i < _map.city(_pos).city_connections().Count(); i++)
		{
			if (!q.Any([i, this](HumanPlayer p) {return p.pos() == _map.city(_pos).city_connections()[i].other_city(_pos).id(); }))
			{
				empty = true;
			}
		}

		if (empty == false)
		{
			return;
		}

		do {
			j = rand() % _map.city(_pos).city_connections().Count();
		} while (q.Any([j, this](HumanPlayer p) {return p.pos() == _map.city(_pos).city_connections()[j].other_city(_pos).id(); }));

		_pos = _map.city(_pos).city_connections()[j].other_city(_pos).id();
	}

	CityId Player::pos() const
	{
		return _pos;
	}

	void Player::InitPosition(CityId city)
	{
		_pos = city;
	}
}