#pragma once
#include "headers.h"
#include "card.h"
#include "deck.h"
#include "player.h"
class Dealer
{
public:
	Dealer();
	~Dealer();
	std::string dealCard();
	std::vector<std::string> returnDeck();
	void topCard();
	void loadDeck(std::vector<std::string>);
private:
	std::string cardDrawn;
	std::vector<std::string> roundDeck;
};

