#pragma once
#include "headers.h"
#include "player.h"
class Human : public Player
{
public:
	~Human();
	std::string playTurn(Player*, std::vector<std::string>, std::vector <int>, int, int);
	std::string menu(Player*, Player*, std::vector<std::string>, std::vector <int>, int, int, int, std::vector<std::string>, std::string);
	void table(std::vector<std::string>, int);
	void handSelect(Player*);
	void layoutSelect(int);
	void helpMenu(Player*, std::vector<std::string>, std::vector <int>);
	int stockMatchMenu(std::vector<int>, std::vector<std::string>, std::string, int);
	void triples(std::vector<std::string>,std::vector<int>, std::vector<std::string>);
private:
	std::string selection;
	std::string handPosition;
	std::string tablePosition;
	std::string playPositon;
	std::string menuInput;
	std::vector<std::string> foundTrip;
	bool correctInput = false;
	int playerNum = 1;
	int count = 0;
	bool canPlay = true;
	bool triple;
	bool suggested;
};

