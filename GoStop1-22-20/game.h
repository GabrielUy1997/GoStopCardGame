#pragma once
#include "headers.h"
#include "player.h"
#include "round.h"
class Game
{
public:
	Game();
	~Game();
	void startGame();
	void askToPlay(int);
	void determineWinner();
	bool newOrLoad();
	void loadGame();
private:
	std::string choice;
	int roundCounter, winner, playerScore, cpuScore, loadNextPlayer;
	bool playAgain, newOrLoads;
	std::vector<int> loadStack;
	std::vector<std::string> loadP1Hand, loadP1Cap, loadP2Hand, loadP2Cap, loadLayout, loadStockPile;
};

