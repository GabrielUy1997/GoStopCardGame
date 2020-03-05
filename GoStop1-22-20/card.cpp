#include "card.h"
#include "deck.h"

Card::Card()
{


}

Card::~Card()
{

}

/**********************************************************************
Function Name: generateCard
Purpose: Used to create all the individual cards and creates a deck out of them
Parameters:
		None
Return Value: A vector of strings that represent the the deck and each index is an individual card
Local Variables:
		None
Algorithm:
		1) Makes a card with a value 1-13 to represent A-K card values and appends the suites for each value to the end of the string
		2) Sends each card to the deck class' add to deck function
		3) After making all the cards returns the full 104 card deck object to the dealer object 
Assistance Received: None
**********************************************************************/
std::vector<std::string> Card::generateCard()
{
	Deck deckObj;
	//assigns value of the card being created
	for (int i = 1; i < 14; i++)
	{
		switch (i)
		{
		case 1:
			val = '1';
			break;
		case 10:
			val = "X";
			break;
		case 11:
			val = 'J';
			break;
		case 12:
			val = 'Q';
			break;
		case 13:
			val = 'K';
			break;
		default:
			val = std::to_string(i);
			break;
		}
		//assigns the suit of the card being created
		for (int j = 0; j < 4; j++) 
		{
			switch (j)
			{
			case 0:
				suit = 'D';
				break;
			case 1:
				suit = 'C';
				break;
			case 2:
				suit = 'H';
				break;
			case 3:
				suit = 'S';
				break;
			default:
				suit = 'X';
				break;
			}
			//combines the value and suit into one string for easier storage
			cardType = val + suit;
			//sends the card to deck class to be added to the gamedeck vector and temp vector
			deckObj.addToDeck(cardType); 
		}
	}
	//combines the two a_decks
	deck = deckObj.makeDeck(deckObj); 
	return deck;
}