#pragma once
#include "headers.h"
#include "dealer.h"
#include "card.h"
#include "deck.h"
#include "cpu.h"
#include "human.h"
class Round
{
public: 
	Round();
	~Round();
	int startRound(Player*, Player*, Player*, int, int, int, int, bool, std::vector<std::string>);
	int loadRound(Player*, Player*, int, std::vector<std::string>, std::vector<int>);
	int goFirst(Player*, Player*, int);
	void showTable();
	Dealer passOutCards(Dealer, Player*, Player*);
	bool isLegal(std::string, std::string);
	void stacksOperatons(std::string, std::string, int, Player*, int);
	void addToLayout(std::string);
	Dealer playStock(Dealer, int);
	void showStats(Player*, Player*, int);
	int roundEnd(Player*, Player*);
	void errorCatch();
	void noPlay(Player*);
	void canPlay(Player*);
	void checkStacks(Player*);
	void checkIfSameHand(Dealer, Player*, Player*);
	int p1Starts(Player*, Player*, int, std::string, bool, Dealer*);
	int p2Starts(Player*, Player*, int, std::string, bool, Dealer*);
	void tripleLayoutCap(Player*);
private:
	int starter, hand, index, stockMatchIndex, winner, tableCounter, stackCounter, cardsStacking, score1, score2;
	std::string play, tempCard, tempTable, threeStack;
	bool addToLay, threeInLay, stockCap3;
	std::string nextPlayer;
	std::string cardDrawn;
	std::string p_cardChosen;
	std::string p_tableChosen;
	std::vector <std::string> tableCards;
	std::vector <int> tableStacks;
	std::vector <std::string> tempStock;
};

