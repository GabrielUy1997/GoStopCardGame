#include "deck.h"
#include "card.h"
#include "dealer.h"

Deck::Deck()
{

}

Deck::~Deck()
{

}

/**********************************************************************
Function Name: addToDeck
Purpose: Used to add cards to the vector that represents the deck
Parameters:
		a_card, string passed by value. It holds the string that represents the card that was just
		created.
Return Value: None
Local Variables:
		None
Algorithm:
		1) Takes the parameter a_card and pushes the value onto the gameDeck and tempDeck vectors
Assistance Received: None
**********************************************************************/
void Deck::addToDeck(std::string a_card) 
{
	//first half of deck getting pushed on to game vector
	gameDeck.push_back(a_card);
	//second half of deck getting pushed on the temp vector
	tempDeck.push_back(a_card); 
}

/**********************************************************************
Function Name: makeDeck
Purpose:  Takes in the Deck obj created in the makeCard() function combines the two 
seperate decks and then shuffles the combined deck
Parameters:
		a_decks, Deck obj passed by value. It holds the 2 full 52 card vectors that
		need to be combined
Return Value: gameDeck
Local Variables:
		seed, used to seed the shuffling.
Algorithm:
		1) Combines the two decks by appending all of the cards in the tempDeck to the end of gameDeck
		2) Shuffles the full 104 card deck
		3) Returns the shuffled gameDeck to the card class
Assistance Received: Ryan king told me about the shuffle function in the algo library and default_random in the random library on 1/23/20
********************************************************************* */
std::vector<std::string> Deck::makeDeck(Deck a_decks)
{
	//combining the two decks
	for (unsigned int i = 0; i < tempDeck.size(); i++) 
	{
		gameDeck.push_back(tempDeck[i]);
	}
	srand(time(NULL));
	unsigned seed = rand() % 104;
	//Using the default_random_engine and the shuffle function to shuffle the deck
	std::shuffle(gameDeck.begin(), gameDeck.end(), std::default_random_engine(seed)); 
	tempDeck.clear();
	return gameDeck;
}

