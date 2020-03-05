#include "human.h"

Human::~Human()
{

}

/**********************************************************************
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
	table(a_table,a_stacks, a_tableCount, a_stackCount); 
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
Assistance Received: None
**********************************************************************/
void Human::table(std::vector<std::string> a_table, std::vector <int> a_stacks, int a_tableCount, int a_stackCount)
{
	std::cout << "Layout cards:\n";
	for (int i = 0; i < a_tableCount; i++)
	{
		std::cout << "[" << i + 1 << "] " << a_table[i] << " ";
	}
	std::cout << "\n";	
}

/**********************************************************************
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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
Function Name:
Purpose:
Parameters:

Return Value: None
Local Variables:
			None
Algorithm:
			1)
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