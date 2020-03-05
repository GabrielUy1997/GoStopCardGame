#include "player.h"

Player::Player(): priority(14) //initiates the priority vector to be size 14
{
	handCount = 10;
	score = 0;
}

Player::~Player()
{

}

/**********************************************************************
Function Name: recieveCard
Purpose: Used to add the card given by the dealer and adding it to the 
players hand
Parameters:
			a_card, string passed by value. Holds the card dealt to the player
Return Value: None
Local Variables:
			None
Algorithm:
			1) Adds the card to the players hand vector
Assistance Received: None
**********************************************************************/
void Player::receiveCard(std::string a_card)
{
	hand.push_back(a_card);
}

/**********************************************************************
Function Name: showHand
Purpose: Used to display the players hand
Parameters:
			None
Return Value: None
Local Variables:
			i, for loop iterator
Algorithm:
			1) Loops through the players hand and prints each card
Assistance Received: None
**********************************************************************/
void Player::showHand()
{
	for (int i = 0; i < handCount; i++)
	{
		std::cout << "[" << i + 1 << "] " << hand[i] << " ";
	}
	std::cout << "\n";
}

/**********************************************************************
Function Name: faceCards
Purpose: Used to determine the highest card value the player has
Parameters:
			None
Return Value: Returns a vector of ints that holds the number of each 
value card the player has and what the highest value is
Local Variables:
			cardPriority, int that holds the value of the highest card
			the player has
			i, for loop iterator
Algorithm:
			1) Looks through the players hand
			2) If a K is found then it increments the index used to
			represent the K cards by one, 13 for K, 12 for Q, 11 for J
			and continues till 1 for 1. It keeps track of the number so
			that ties can be broken if both players have the same highest
			value then who ever has the most of that card goes first
			3) The highest value card is stored in the first index of the 
			vector then the vector is returned
Assistance Received: None
**********************************************************************/
std::vector<int> Player::faceCards()
{
	int cardPriority = 0;
 	for (unsigned int i = 0; i < hand.size(); i++)
	{
		size_t found = hand[i].find("K");
		if (found != std::string::npos)
		{
			cardPriority = 13;
			priority[13]++;
		}
		found = hand[i].find("Q");
		if (found != std::string::npos)
		{
			if (cardPriority < 12)
			{
				cardPriority = 12;
			}
			priority[12]++;
		}
		found = hand[i].find("J");
		if (found != std::string::npos)
		{
			if(cardPriority < 11)
			{
				cardPriority = 11;
			}
			priority[11]++;
		}
		found = hand[i].find("X");
		if (found != std::string::npos)
		{
			if (cardPriority < 10)
			{
				cardPriority = 10;
			}
			priority[10]++;
		}
		else
		{
			if (cardPriority < 1)
			{
				cardPriority = 1;
			}
			for (int j = 9; j > 1; j--)
			{
				std::string temp = std::to_string(j);
				size_t found = hand[i].find(temp);
				if (found != std::string::npos)
				{
					priority[j]++;
					if(cardPriority < j)
					{ 
						cardPriority = j;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	priority[0] = cardPriority;
	return priority;
}

/**********************************************************************
Function Name: playTurn
Purpose: Used to allow player to play their turn, this is a virtual function so
the human and Computer classes have their own specific playTurn functions
Parameters:
			a_player, pointer to a Player obj. Represents the the current
			player whos turn it is
			a_table, vector of strings passed by value. The cards in the layout
			a_stacks, vector of ints passed by value. Used 
			to represent if there are any 3 stacks on the layout
			a_tableCount, int passed by value. How many cards are in the layout
			a_stackCount, int passed by value. Stacks in the layout
Return Value: None
Local Variables:
			None
Algorithm:
			1) None
Assistance Received: None
**********************************************************************/
std::string Player::playTurn(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_tableCount, int a_stackCount)
{
	std::cout << "What Card would you like to play?\n";
	std::string index = "f";
	return index;
}

/**********************************************************************
Function Name: pullCard
Purpose: Pulls the card from the players hand
Parameters:
			a_index, int passed by value. The index chosen
Return Value: The card in the chosen index of the hand
Local Variables:
			None
Algorithm:
			1) Gets the value from the index chosen then returns it
Assistance Received: None
**********************************************************************/
std::string Player::pullCard(int a_index)
{
	return hand[a_index];
}

/**********************************************************************
Function Name: removeCard
Purpose: Removes a card from the hand of a player
Parameters:
			a_index, int passed by value. Index of the card being removed
Return Value: None
Local Variables:
			None
Algorithm:
			1) Erases the index given from the player hand
			2) Decrement the players handCount by 1
Assistance Received: None
**********************************************************************/
void Player::removeCard(int a_index)
{
	hand.erase(hand.begin() + a_index);
	handCount--;
}

/**********************************************************************
Function Name: addCapture
Purpose: Deals with adding cards that were captured to the capture pile,
and to add the points to the players score when they have 4 of a kind
Parameters:
			a_capt, string passed by value. The card being captured
			a_card, string passed by value. The card from the players hand
			a_num, int passed by value. Denotes if the layout card is a 3 stack or not
			a_triple, bool passed by value. If three seperate cards were captured 
			from the layout
			a_cards, string passed by value. The other two cards being captured when
			the player is capturing three seperate cards
Return Value: None
Local Variables:
			combineIndex, int
Algorithm:
			1)
Assistance Received: None
**********************************************************************/
void Player::addCapture(std::string a_capt, std::string a_card, int a_num, bool a_triple, std::string a_cards)
{
	int combineIndex = 0;
	int stackCount = 0;
	std::string capturedStack;
	if (a_num == 4) //4 stack
	{
		roundScore++;
		score++;
		if (a_triple == true)
		{
			capturedStack += a_capt + " ";
			capturedStack += a_card + " ";
			capturedStack += a_cards;
			capturePile.push_back(capturedStack);
			std::cout << capturedStack;
			return;
		}
	}
	else if (a_num == 2) //2 stack
	{
		for (unsigned int i = 0; i < capturePile.size(); i++)
		{
			if (a_capt[0] == capturePile[i][0]) //checks if the player has any other captured pairs of the same card to combine into a 4-stack
			{
				stackCount++;
				if (capturePile[i][2] == ' ')
				{
					stackCount++;
				}
				if (stackCount == 2 && capturePile[i].length() < 7)
				{
					std::cout << "Your 2 pairs of " << a_capt[0] << " cards combine to a 4 stack and give you a point!" << "\n";
					a_capt = a_capt + " " + a_card + " " + capturePile[i];
					capturedStack += a_capt;
					capturePile.push_back(capturedStack);
					std::cout << capturedStack;
					combineIndex = i;
					capturePile.erase(capturePile.begin() + combineIndex);
					roundScore++;
					score++;
					a_num = 4; //making it a 4 stack
					combineIndex = 1;
					return;
				}
			}
		}
	}
	//capturedStack = std::to_string(a_num);

	if (a_card[2] == '-')
	{
		a_card[2] = ' ';
		a_card[5] = ' ';
	}
	capturedStack += a_capt;
	capturedStack += " ";
	capturedStack += a_card;
	capturePile.push_back(capturedStack);
	std::cout << capturedStack;
}

/**********************************************************************
Function Name: showScore
Purpose: Returns the players score
Parameters:
			None
Return Value: The players score, int
Local Variables:
			None
Algorithm:
			1) Returns the score
Assistance Received: None
**********************************************************************/
int Player::showScore()
{
	return score;
}

/**********************************************************************
Function Name: showCapturePile
Purpose: Shows the players capture pile
Parameters:
			None
Return Value: None
Local Variables:
			i, for loop iterator
Algorithm:
			1) Prints out all the cards in the players hand
Assistance Received: None
**********************************************************************/
void Player::showCapturePile()
{
	std::cout << "Capture Pile: ";
	for (unsigned int i = 0; i < capturePile.size(); i++)
	{
		std::cout << capturePile[i] << " ";
	}
	std::cout << "\n";
}

/**********************************************************************
Function Name: returnHand
Purpose: returns the hand of the player
Parameters:
			None
Return Value: The players hand, vector of strings
Local Variables:
			None
Algorithm:
			1) Return the players hand
Assistance Received: None
**********************************************************************/
std::vector<std::string> Player::returnHand()
{
	return hand;
}

/**********************************************************************
Function Name: anyTableOption
Purpose: Checks if the player can make a play on any cards on the layout
Parameters:
			a_table, vector of strings passed by value. The cards
			in the layout
			a_player, pointer to a Player obj. The player currently
			playing
Return Value: If the player can make a play on anything on the layout,
bool
Local Variables:
			i, for loop iterator
			j, for loop iterator
Algorithm:
			1) Search layout for any matches with a card from the hand
			2) If there is a match return true, if not then return false
Assistance Received: None
**********************************************************************/
bool Player::anyTableOption(std::vector<std::string> a_table, Player* a_player)
{
	for (unsigned int i = 0; i < a_player->hand.size(); i++)
	{
		for (unsigned int j = 0; j < a_table.size(); j++)
		{
			if (a_player->hand[i][0] == a_table[j][0])
			{
				return true;
			}
		}
	}
	return false;
}

/**********************************************************************
Function Name: menu
Purpose: Used to collect input from player of what they would like to
do, this is the virtual function so Human and Computer have their own menu
functions
Parameters:
			a_player, pointer to a Player obj. Represents the Human player
			a_player2, pointer to a Player obj. Represents the Computer player
			a_table, vector of strings passed by value. The cards in the layout
			a_stacks, vector of ints passed by value. Used to represent which cards
			are 3 stacks
			a_round, int passed by value. The current round
			a_score1, int passed by value. The Human player's score
			a_score2, int passed by value. The Computer player's score
			a_stock, vector of strings passed by value. The vector holding the 
			cards remaining in the stock pile
			a_next, string passed by value. The current player
Return Value: None
Local Variables:
			None
Algorithm:
			1) Nothing, Human and computer use their own
Assistance Received: None
**********************************************************************/
std::string Player::menu(Player* a_player, Player* a_player2, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_round, int a_score1, int a_score2, std::vector<std::string> a_stock, std::string a_next)
{

	return "p";
}

/**********************************************************************
Function Name: serialize
Purpose: Saving the state of the game to a serialization file
Parameters:
			a_player, pointer to a Player obj. Represents the Human player
			a_player2, pointer to a Player obj. Represents the Computer player
			a_table, vector of strings passed by value. The cards in the layout
			a_stacks, vector of ints passed by value. Used to represent which cards
			are 3 stacks
			a_round, int passed by value. The current round
			a_score1, int passed by value. The Human player's score
			a_score2, int passed by value. The Computer player's score
			a_stock, vector of strings passed by value. The vector holding the 
			cards remaining in the stock pile
			a_next, string passed by value. The current player
Return Value: None
Local Variables:
			i,j,k,l,m,n,o, for loop iterators
Algorithm:
			1) Asks the the user what file they would like to save to,
			then either creates one or saves to an existing one
			2) Saves both players scores, hands, and capture piles, the layout,
			round number, the stock pile, and whos turn the game was saved on
Assistance Received:https://www.geeksforgeeks.org/file-handling-c-classes/
**********************************************************************/
void Player::serialize(Player* a_player, Player* a_player2, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_round, int a_score1, int a_score2, std::vector<std::string> a_stock, std::string a_next)
{
	//got the basic set up of this function from https://www.geeksforgeeks.org/file-handling-c-classes/ 2/12/20
	std::fstream fio;
	std::string line;
	std::string input = " ";
	do
	{
		std::cout << "Please input a file name with the extention .txt:";
		std::cin >> input;

		size_t found = input.find(".txt", (input.size() - 4), 4);
		if (found != std::string::npos)
		{
			std::cout << "Saved to file, now exiting game.\n";
			dashedLine();
			fio.open(input, std::ios::trunc | std::ios::out | std::ios::in);

			while (fio)
			{
				fio << "Round: " << a_round;
				fio << "\n\n";
				fio << "Computer:\n";
				fio << "   Score: " << a_player2->score << "\n";
				fio << "   Hand: ";
				for (unsigned int i = 0; i < a_player2->hand.size(); i++)
				{
					fio << a_player2->hand[i] << " ";
				}
				fio << "\n";
				fio << "   Capture Pile: ";
				for (unsigned int j = 0; j < a_player2->capturePile.size(); j++)
				{
					fio << a_player2->capturePile[j] << " ";
				}
				fio << "\n";
				fio << "Human:\n";
				fio << "   Score: " << a_player->score << "\n";
				fio << "   Hand: ";
				for (unsigned int k = 0; k < a_player->hand.size(); k++)
				{
					fio << a_player->hand[k] << " ";
				}
				fio << "\n";
				fio << "   Capture Pile: ";
				for (unsigned int m = 0; m < a_player->capturePile.size(); m++)
				{
					fio << a_player->capturePile[m] << " ";
				}
				fio << "\n\n";
				fio << "Layout: ";
				for (unsigned int n = 0; n < a_table.size(); n++)
				{
					fio << a_table[n] << " ";
				}
				fio << "\n\n";
				fio << "Stock Pile: ";
				for (unsigned int o = 0; o < a_stock.size(); o++)
				{
					fio << a_stock[o] << " ";
				}
				fio << "\n\n";
				fio << "Next Player is: " << a_next;
				fio << "\n\n";
				break;
			}

			fio.close();
			break;
		}
		else
		{
			std::cout << "invalid file\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: stockMatchMenu
Purpose: Used for matching the stock cards with cards on the layout,
this is a virtual function so the Human and Computer classes use their
own specific function
Parameters:
			a_matchList, vector of ints passed by value.
			a_list, vector of strings passed by value.
			a_cardDrawn, string passed by value.
			a_stockIndex, int passed by value.
Return Value: The index of the card on the layout that was selected,
				int
Local Variables:
			i, for loop iterator
Algorithm:
			1) virtual function, but used to look for matches in the 
			layout with the stock card pulled
Assistance Received: None
**********************************************************************/
int Player::stockMatchMenu(std::vector<int> a_matchList, std::vector<std::string> a_list, std::string a_cardDrawn, int a_stockIndex)
{
	int a_input;
	for (unsigned int i = 0; i < a_matchList.size(); i++)
	{
		std::cout << "[" << i + 1 << "]" << a_list[a_matchList[i]] << " ";
	}
	do
	{
		std::cout << "\nWhich card would you like to stack on?: ";
		std::cin >> a_input;
		a_input--;
		if (a_input < a_matchList.size() || a_input >= 0)
		{
			std::cout << "The stock card created a pair on the layout with " << a_cardDrawn << " and " << a_list[a_matchList[a_input]] << "\n";
			a_stockIndex = a_matchList[a_input];
			return a_stockIndex;
		}
		else
		{
			std::cout << "Invalid input try again\n";
		}
	} while (true);
	exit(EXIT_FAILURE);
}

/**********************************************************************
Function Name: clearHand
Purpose: clears the players hand, used if the hands need to be re-delt
Parameters:
			None
Return Value: None
Local Variables:
			None
Algorithm:
			1) Clears the hand vector
Assistance Received: None
**********************************************************************/
void Player::clearHand()
{
	hand.clear();
}

/**********************************************************************
Function Name: loadGame
Purpose: loads the hand, hand size, and capture pile given by a load file
Parameters:
			a_hand, vector of strings passed by value. The players hand
			from the load file
			a_cap, vector of strings passed by value. The players capture
			pile from the load file
			a_score, int passed by value. The players score from the load
			file
Return Value: None
Local Variables:
			None
Algorithm:
			1) Sets hand from the load file to the players hand
			2) Sets capture pile from load file to the players capture
			pile
Assistance Received: None
**********************************************************************/
void Player::loadGame(std::vector<std::string> a_hand, std::vector<std::string> a_cap, int a_score)
{
	hand = a_hand;
	handCount = hand.size();
	capturePile = a_cap;
	//score = a_score;
	return;
}

/**********************************************************************
Function Name: loadScore
Purpose: loads the players score from the load file
Parameters:
			a_score, int passed by value. The players score from the 
			load file
Return Value: Players score, int
Local Variables:
			None
Algorithm:
			1) Sets the loaded score to the current players score and
			returns the score
Assistance Received: None
**********************************************************************/
int Player::loadScore(int a_score)
{
	score = a_score;
	return score;
}

/**********************************************************************
Function Name: returnRoundScore
Purpose: returns the players score for the current round
Parameters:
			None
Return Value: The players score for the current round
Local Variables:
			None
Algorithm:
			1) Return the players score
Assistance Received: None
**********************************************************************/
int Player::returnRoundScore()
{
	return roundScore;
}

/**********************************************************************
Function Name: helpMenu
Purpose: The help menu used that can be used by the Human player,
this is a virtual function so the Human has its own specific
function
Parameters:
			a_player, pointer to a player obj.
			a_table, vector of strings passed by value.
			a_stacks, vector of ints passed by value.
Return Value: None
Local Variables:
			None
Algorithm:
			1) Virtual function, so the fucntion used is in the Human
			class
Assistance Received: None
**********************************************************************/
void Player::helpMenu(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks)
{

}

/**********************************************************************
Function Name: loadRoundScore
Purpose: loads the players score when loading in a file
Parameters:
		None
Return Value: None
Local Variables:
			stackCount, int. Used to hold the value of the current
			card being looked at in the capture pile
			match, string. Used to hold the string value of the current
			card being looked at in the capture pile
			stackIndexes[], vector of ints that keeps track of how many
			of each card is in the players capture pile
Algorithm:
			1) Reads through the players capture pile and counts how many
			of each type of card they have
			2) If the player each pair of 4 of a card they have adds a
			point to their score
Assistance Received: None
**********************************************************************/
void Player::loadRoundScore()
{
	int stackCount = 0;
	std::string match;
	std::vector<int> stackIndexes(14, 0);
	for (unsigned int i = 0; i < capturePile.size(); i++)
	{
		match = capturePile[i][0];//gets the type of card in the index of capPile
		if (match == "X")
		{
			match = "10";
		}
		else if (match == "J")
		{
			match = "11";
		}
		else if (match == "Q")
		{
			match = "12";
		}
		else if (match == "K")
		{
			match = "13";
		}
		stackCount = stoi(match); //converts it to int so it can be added to the list of that type
		stackIndexes[stackCount]++;
	}
	for (unsigned int j = 0; j < stackIndexes.size(); j++)
	{
		if (stackIndexes[j] / 4 >= 1 && stackIndexes[j] != 0)
		{
			roundScore += (stackIndexes[j] / 4);
			score += (stackIndexes[j] / 4);
		}
	}
}

/**********************************************************************
Function Name: getCapturePile
Purpose: Returns the players capture pile
Parameters:
			None
Return Value: The players capture pile, a vector of strings
Local Variables:
			None
Algorithm:
			1) Return the players capture pile
Assistance Received: None
**********************************************************************/
std::vector<std::string> Player::getCapturePile()
{
	return capturePile;
}

/**********************************************************************
Function Name: isInCapPile
Purpose: Checks whether there are cards in the players capture pile
that match a card they have in their hand
Parameters:
			a_player, a pointer to a Player obj. The player whos
			capture pile is being checked
			a_cardType, char. The value of the type of card being looked
			for
Return Value: If there is a match or not, bool
Local Variables:
			i, for loop iterator
			tempCap, vector of strings that temporarily holds the 
			players capture pile
Algorithm:
			1) Get the current players capture pile
			2) Look through the players capture pile
			to find any matches
			3) Either return true if a match was found or
			false if there is no match
Assistance Received: None
**********************************************************************/
bool Player::isInCapPile(Player* a_player, char a_cardType)
{
	std::vector<std::string> tempCap = a_player->getCapturePile();
	for (int i = 0; i < tempCap.size(); i++)
	{
		if (tempCap[i][0] == a_cardType)
		{
			return true;
		}
	}
	return false;
}