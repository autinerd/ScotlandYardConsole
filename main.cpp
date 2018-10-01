#include <iostream>
#include "map.hpp"
#include "gamemanager.hpp"
#define println(x) std::cout << x << std::endl

int main()
{
	std::string input("Input/small.input");
	println("Herzlich willkommen bei Scotland Yard, der spannenden Jagd nach dem Mister X!");
	int answerPlayers = -1;
	int answerRounds = -1;
	do {
		std::cout << "Mit wievielen Spielern wollt ihr spielen? ";
		std::cin >> answerPlayers;
	} while (answerPlayers < 1);
	do {
		std::cout << "Und wieviele Runden wollt ihr spielen? ";
		std::cin >> answerRounds;
	} while (answerRounds < 1);
	println("Los geht's...");
	ScotlandYard::GameManager manager(answerPlayers, input, (size_t)answerRounds);
	return 0;
}
