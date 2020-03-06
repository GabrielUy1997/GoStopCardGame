#pragma once
#include "player.h"
class Cpu : public Player
{
public:
	~Cpu();
	std::string playTurn(Player*, std::vector<std::string>, std::vector <int>, int, int);
	std::string moveSelector(Player*, std::vector<std::string>, std::vector <int>);
	std::string checkForTriple(Player*, std::vector<std::string>, std::vector <int>, std::vector<std::string>);
	std::string menu(Player*, Player*, std::vector<std::string>, std::vector <int>, int, int, int, std::vector<std::string>, std::string);
	int stockMatchMenu(std::vector<int>, std::vector<std::string>, std::string, int);
private:
	std::string selection;
	std::string menuInput;
	std::vector<std::string> foundTrip;
	int playerNum = 2;
	bool canPlay = true;
};

