#pragma once
#include "headers.h"
#include "card.h"
class Deck
{
public:
	Deck();
	~Deck();
	void addToDeck(std::string);
	std::vector<std::string> makeDeck(Deck);
private:
	std::vector<std::string> gameDeck;
	std::vector<std::string> tempDeck;
};

