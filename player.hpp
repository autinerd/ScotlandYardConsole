#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "base.hpp"
#include "map.hpp"
#include <string>

namespace ScotlandYard
{
	class Player
	{
	public:
		Player(Map map_, std::string name_);
		virtual void move() = 0;
		std::string const & name() const;
		CityId pos() const;
		void InitPosition(CityId city);
	protected:
		std::string _name;
		CityId _pos;
		Map _map;
	private:

	};

	class HumanPlayer : public Player
	{
	public:
		// Use constructor of base class (i.e. we can use HumanPlayer("Hans") to construct a HumanPlayer
		using Player::Player;
		void move();
	private:
	};

	class MisterX : public Player
	{
	public:
		MisterX(Map map_);
		void move();
		void moveMisterX(Queryable<HumanPlayer> const & q);
	private:
	};

} //namespace ScotlandYard
#endif //!PLAYER_HPP
