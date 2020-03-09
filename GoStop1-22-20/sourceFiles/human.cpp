#include "human.h"

Human::~Human()
{

}

/**********************************************************************
Function Name: playTurn
Purpose: Takes in the Human players inputs when they play their turn
Parameters:
		a_player, pointer to a Player obj. Represents the the current
		player whos turn it is
		a_table, vector of strings passed by value. The cards in the layout
		a_stacks, vector of ints passed by value. Used 
		to represent if there are any 3 stacks on the layout
		a_tableCount, int passed by value. How many cards are in the layout
		a_stackCount, int passed by value. Stacks in the layout
Return Value: A string with the indexes of the card they wanna play
from their hand and from the layout
Local Variables:
		playerHand, vector of strings. Used to temporaritly hold the 
		players hand
Algorithm:
			1) Checks if the player has any available plays, if not
			then it asks what card they would like to add to the layout
			and returns that selection
			2) Asks what card the player wants to play from their hand
			3) Asks what card they would like to play on the layout
			4) If the player didnt ask for help then check for any 
			possible 3 capures on the board
			5) If 3 of the same card are found then make then add the
			index of all 3 of the cards to the playPosition string
			6) If there are no 3 captures on the board then the play is 
			just the 2 indexes chosen by the player
			7) Return the playPostion string
Assistance Received: None
**********************************************************************/
std::string Human::playTurn(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_tableCount, int a_stackCount)
{
	canPlay = anyTableOption(a_table, a_player);
	if (canPlay == false)
	{
		std::cout << "No play available\n";
		a_player->showHand();
		dashedLine();
		std::cout << "What card would you like to add to the layout?\n";
		handSelect(a_player);
		return handPosition;
	}
	playPositon = " ";
	//shows table
	table(a_table,a_tableCount); 
	std::cout << "Player hand:\n";
	a_player->showHand();
	dashedLine();
	handSelect(a_player);
	correctInput = false;
	selection = " ";
	layoutSelect(a_tableCount);
	std::vector<std::string> playerHand = a_player->returnHand();
	if (menuInput != "3")
	{
		triples(playerHand, a_stacks, a_table);
	}
	if (triple == true)
	{
		std::string i = foundTrip.at(foundTrip.size() - 4);
		char f = foundTrip.back()[0];
		if (handPosition != foundTrip[(foundTrip.size() - 1)] || tablePosition != foundTrip[(foundTrip.size() - 4)])
		{
			playPositon = 'x';
		}
		else if (handPosition[0] == f && tablePosition[0] == i[0])
		{
			playPositon = (foundTrip.at(foundTrip.size() - 1)) + (foundTrip.at(foundTrip.size() - 4)) + (foundTrip.at(foundTrip.size() - 3)) + (foundTrip.at(foundTrip.size() - 2));
		}
		triple = false;
	}
	else
	{
		triple = false;
		playPositon = handPosition + tablePosition;
	}
	return playPositon;
}

/**********************************************************************
Function Name: menu
Purpose: The menu the Human player sees and uses to play the game
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
Return Value: Their choice in the menu, a string
Local Variables:
			None
Algorithm:
			1) Asks what the player would like to do
			2) Takes in the input and either calls the 
			serialize function to save the game or return
			play, help, or exit
Assistance Received: None
**********************************************************************/
std::string Human::menu(Player* a_player, Player* a_player2, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_round, int a_score1, int a_score2, std::vector<std::string> a_stock, std::string a_next)
{
	do
	{
		dashedLine();
		std::cout << "Player turn, what would you like to do?\n";
		std::cout << "1.Save Game\n" << "2.Make Move\n" << "3.Ask for Help\n" << "4.Quit game\n";
		std::cin >> menuInput;
		if (menuInput == "1")
		{
			std::cout << "Saving\n";
			serialize(a_player, a_player2, a_table, a_stacks, a_round, a_score1, a_score2, a_stock, a_next);
			exit(0);
		}
		else if (menuInput == "2")
		{
			return "play";
		}
		else if (menuInput == "3")
		{
			return "help";
		}
		else if (menuInput == "4")
		{
			return "exit";
		}
		else
		{
			std::cout << "Invalid input, please enter a valid one:\n";
		}
	} while (true);
	dashedLine();
	return false;
}

/**********************************************************************
Function Name: table
Purpose: Show the layout cards
Parameters:
		a_table, vector of strings. The layout cards
		a_tableCount, int. Number of cards in the layout
Return Value: None
Local Variables:
		None
Algorithm:
		1) Loops through the vector holding the layout cards and prints 
		them
Assistance Received: None
**********************************************************************/
void Human::table(std::vector<std::string> a_table, int a_tableCount)
{
	std::cout << "Layout cards:\n";
	for (int i = 0; i < a_tableCount; i++)
	{
		std::cout << "[" << i + 1 << "] " << a_table[i] << " ";
	}
	std::cout << "\n";	
}

/**********************************************************************
Function Name: handSelect
Purpose: Used for when the player is chosing the card they 
want to play from their hand
Parameters:
		a_player, pointer to a player obj. Used to access the
		correct players hand
Return Value: None
Local Variables:
		tempHand, vector of strings. Holds the players 
		cards temporarily
Algorithm:
			1) Asks what card the player wants to play
			2) The player enters the index
			3) The input is then stored in the handPosition
			variable
Assistance Received: None
**********************************************************************/
void Human::handSelect(Player* a_player)
{
	std::vector<std::string> tempHand;
	tempHand = a_player->returnHand();
	int tempCount = tempHand.size(), input;
	do
	{
		std::cout << "What card would you like to play?\n";
		std::cout << "Enter the index:";
		std::cin >> selection;
		input = stoi(selection);
		input--;
		if (input < tempCount && input >= 0)
		{
			handPosition = std::to_string(input);
			break;
		}
		else
		{
			std::cout << "Invalid entry try again\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: layoutSelect
Purpose: Used for when the player is selecting where they are gonna 
play their card in the layout
Parameters:
		a_tableCount, int. The number of cards in the layout
Return Value: None
Local Variables:
		None
Algorithm:
			1) Asks the player what index they would like to play to
			2) Takes in the input
			3) Stores the input in the tablePosition variable
Assistance Received: None
**********************************************************************/
void Human::layoutSelect(int a_tableCount)
{
	int input;
	do {
		std::cout << "Where would you like to play the card?\n";
		std::cout << "Enter the index:";
		std::cin >> selection;
		input = stoi(selection);
		input--;
		if (input < a_tableCount && input >= 0)
		{
			tablePosition = std::to_string(input);
			break;
		}
		else
		{
			std::cout << "Invalid entry try again\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: helpMenu
Purpose: Used when the Human player selects help in the menu
Parameters:
		a_player, pointer to a Player obj. Used to know what player is 
		currently being used
		a_table, vector of strings passed by value. The layout cards
		a_stacks, vector of ints passed by value. Stacks in the layout
Return Value: None
Local Variables:
		playerHand, vector of strings. Players hand
		capPair, bool. If there are matching cards in the players
		capture pile
		h, int. Hand index
		t, int. Table index
		i and j, for loop iterator
Algorithm:
		1) Gets the players hand
		2) Checks for 3 matching cards in the layout
		3) If the help function hasnt suggested a play yet,
		look through the players hand and the players capture
		pile and look for any matches
		4) If any matches are found then recommend they play the card
		that matches, if no matches are found in the capture pile
		then recommend any matches found in the layout and the hand,
		and if none are found then tell the player to add a card to 
		the layout
Assistance Received: None
**********************************************************************/
void Human::helpMenu(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks)
{
	std::vector<std::string> playerHand;
	playerHand = a_player->returnHand();
	dashedLine();
	bool capPair = false;
	int h;
	int t;
	triples(playerHand, a_stacks, a_table);
	if (suggested == false)
	{
		for (unsigned int i = 0; i < playerHand.size(); i++)
		{
			capPair = isInCapPile(a_player, playerHand[i][0]);
			for (unsigned int j = 0; j < a_table.size(); j++)
			{
				if (capPair == true && playerHand[i][0] == a_table[j][0])
				{
					std::cout << "I recommend you play " << playerHand[i] << " on " << a_table[j] << " to complete the pair matching a pair in the capture pile\n";
					suggested = true;
					return;
				}
				else if (capPair == false && playerHand[i][0] == a_table[j][0])
				{
					suggested = true;
					h = i;
					t = j;
				}
			}
		}
		if (suggested == true)
		{
			std::cout << "I recommend you play " << playerHand[h] << " on " << a_table[t] << " to complete the pair\n";
		}
		else if (suggested == false)
		{
			std::cout << "No possible play, you must add a card to the layout\n";
		}
	}
	dashedLine();
}

/**********************************************************************
Function Name: stockMatchMenu
Purpose: Used for matching the stock cards with cards on the layout
Parameters:
		a_matchList, vector of ints passed by value. The list of 
		matches in the layout
		a_list, vector of strings passed by value. The layout
		cards
		a_cardDrawn, string passed by value. The stock card
		a_stockIndex, int passed by value. Index of the matching
		card
Return Value: The index of the card on the layout that was selected,
		int
Local Variables:
		a_input, int. Used to collect the users input
		i, for loop iterator
Algorithm:
		1) Prints the list of matches found for the stock card
		2) Asks the player which one they would like to capture
		3) Prints what they are capturing and returns their
		selection
Assistance Received: None
**********************************************************************/
int Human::stockMatchMenu(std::vector<int> a_matchList, std::vector<std::string> a_list, std::string a_cardDrawn, int a_stockIndex)
{
	int a_input;
	do
	{
		std::cout << "Multiple matches for the stock card: ";
		for (int i = 0; i < a_matchList.size(); i++)
		{
			std::cout << "[" << i + 1 << "]" << a_list[a_matchList[i]] << " ";
		}
		std::cout << "\nWhich card would you like to stack on?: ";
		std::cin >> a_input;
		a_input--;
		if (a_input < a_matchList.size() && a_input >= 0)
		{
			std::cout << "The Player used the stock card to create a pair on the layout with " << a_cardDrawn << " and " << a_list[a_matchList[a_input]] << "\n";
			a_stockIndex = a_matchList[a_input];
			return a_stockIndex;
			break;
		}
		else
		{
			std::cout << "Invalid input try again\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: triples
Purpose: Searches for any 3 cards with the same value in the layout
that can be captured by the player
Parameters:
		a_playerHand, vector of strings. The players hand
		a_stacks, vector of ints. Stacks on the layout
		a_table, vector of strings. The table cards
Return Value: None
Local Variables:
			None
Algorithm:
			1) Compares the players hand to the layout
			2) If the player asked for help then it prints the 
			recommendation
			3) Searches the layout to find any 3 cards matching the 
			player card
Assistance Received: None
**********************************************************************/
void Human::triples(std::vector<std::string> a_playerHand, std::vector<int> a_stacks, std::vector<std::string> a_table)
{
	for (unsigned int i = 0; i < a_playerHand.size(); i++)
	{
		for (unsigned int j = 0; j < a_table.size(); j++)
		{
			if (a_stacks[j] == 2 && a_playerHand[i][0] == a_table[j][0])
			{
				if (menuInput == "3")
				{
					std::cout << "I recommend you play " << a_playerHand[i] << " on " << a_table[j] << " to complete the triple stack\n";
					suggested = true;
					return;
				}
			}
			else if (a_table[j][0] == a_playerHand[i][0])
			{
				count++;
				foundTrip.push_back(std::to_string(j));
				if (count >= 3)
				{
					foundTrip.push_back(std::to_string(i));
					int k = stoi(foundTrip.at(foundTrip.size() - 4));
					if (menuInput == "3")
					{
						std::cout << "I recommend you play " << a_playerHand[i] << " on index " << a_table[k] << " to capture three " << a_table[j][0] << " cards on the layout\n";
					}
					suggested = true;
					triple = true;
					count = 0;
					return;
				}
			}
			else
			{
				suggested = false;
			}
		}
		count = 0;
	}
}
