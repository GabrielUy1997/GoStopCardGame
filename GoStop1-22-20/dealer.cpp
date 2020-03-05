#include "dealer.h"

Dealer::Dealer()
{
	Card makeCards;
	roundDeck = makeCards.generateCard();
}

Dealer::~Dealer()
{

}


/**********************************************************************
Function Name: dealCard
Purpose: Draws the card at the top of the deck and returns the string denoting the card.
Parameters:
		None
Return Value: A string that represents the card at the top of the deck object
Local Variables:
		None
Algorithm:
		1) Takes the card at the top of the deck obj
		2) Erases the card from the vector
		3) Returns the string representing the card
Assistance Received: None
**********************************************************************/
std::string Dealer::dealCard()
{
	cardDrawn = roundDeck[0];
	roundDeck.erase(roundDeck.begin());
	return cardDrawn;
}

/**********************************************************************
Function Name: topCard
Purpose: Show what the card at the top of the deck is
Parameters:
		None
Return Value: None
Local Variables:
		None
Algorithm:
		1) Prints the card that is stored at index 0 of the roundDeck vector
Assistance Received: None
**********************************************************************/
void Dealer::topCard()
{
	std::cout << roundDeck[0] << "\n";
}

/**********************************************************************
Function Name: returnDeck
Purpose: Returns the current deck so that the order of the cards are the same
Parameters:
		None
Return Value: None
Local Variables:
		None
Algorithm:
		1) Returns the roundDeck vector
Assistance Received: None
**********************************************************************/
std::vector<std::string> Dealer::returnDeck()
{
	return roundDeck;
}

/**********************************************************************
Function Name: loadDeck
Purpose: Used to load the correct deck given by the load file
Parameters:
		a_deck, vector of strings passed by value. It holds the deck that was
		read from the load file.
Return Value: None
Local Variables:
		None
Algorithm:
		1) Assigns the roundDeck to be equal to the loaded deck using a_deck
Assistance Received: None
**********************************************************************/
void Dealer::loadDeck(std::vector<std::string> a_deck)
{
	roundDeck = a_deck;
	return;
}