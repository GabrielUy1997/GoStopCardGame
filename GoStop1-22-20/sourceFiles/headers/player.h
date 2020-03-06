#pragma once
#include "headers.h"
#include "dealer.h"
#include "card.h"
class Player
{
public:
	Player();
	~Player();
	void receiveCard(std::string);
	void showHand();
	std::vector<int> faceCards();
	virtual std::string playTurn(Player*, std::vector<std::string>, std::vector <int>, int, int);
	virtual std::string menu(Player*, Player*, std::vector<std::string>, std::vector <int>, int, int, int, std::vector<std::string>, std::string);
	virtual void serialize(Player*, Player*, std::vector<std::string>, std::vector <int>, int, int, int, std::vector<std::string>, std::string);
	virtual int stockMatchMenu(std::vector<int>, std::vector<std::string>, std::string, int);
	virtual void helpMenu(Player*, std::vector<std::string>, std::vector <int>);
	std::string pullCard(int);
	void removeCard(int);
	void addCapture(std::string, std::string, int, bool, std::string);
	int showScore();
	void showCapturePile();
	std::vector<std::string> returnHand();
	bool anyTableOption(std::vector<std::string>, Player*);
	void loadGame(std::vector<std::string>, std::vector<std::string>, int);
	void clearHand();
	int loadScore(int);
	int returnRoundScore();
	void loadRoundScore();
	std::vector<std::string> getCapturePile();
	bool isInCapPile(Player*, char);
private:
	int handCount, score, roundScore;
	std::vector<std::string> hand;
	std::vector<std::string> capturePile;
	std::vector<int> priority;
};

