#pragma once
#include "headers.h"
class Card
{
public:
	Card();
	~Card();
	std::vector<std::string> generateCard(); //function used to make each card, called in constructor
private:
	std::string suit;
	std::string val;
	std::string cardType;
	std::vector<std::string> deck;
};

