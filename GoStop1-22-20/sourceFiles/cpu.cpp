#include "cpu.h"


Cpu::~Cpu()
{

}

/**********************************************************************
Function Name: playTurn
Purpose: Used for the Computer player to choose their play
Parameters:
		a_player, pointer to a Player obj.
		a_table, vector of strings. 
		a_stacks, vector of ints.
		a_tableCount, int.
		a_stackCount, int.
Return Value: The Computer players move selection, a string
Local Variables:
			None
Algorithm:
			1) Checks if the Computer player can make a play
			2) If the Computer player doesnt have a play
			return 0
			3) If they do have a play then make a selection
Assistance Received: None
**********************************************************************/
std::string Cpu::playTurn(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_tableCount, int a_stackCount)
{
	canPlay = anyTableOption(a_table, a_player);
	if (canPlay == false)
	{
		a_player->showHand();
		return "0";
	}
	selection = moveSelector(a_player, a_table, a_stacks);
	return selection;
}

/**********************************************************************
Function Name: moveSelector
Purpose: Used to determine and describe what the Computer player will play
Parameters:
		a_player, a pointer to a Player obj. The current player playing
		a_table, vector of strings. The layout cards
		a_stacks, vector of ints. The stacks on the layout
Return Value: The positions in the hand and in the layout that the 
Computer player is going to play, string
Local Variables:
			cpuHand, vector of strings that temporarily holds the 
			players hand
			playPosition, holds the positions in the hand and index
			that the cpu player is going to select
			handPos, The index in the hand the cpu is going to play
			tablePos, The index of the table that the cpu is going 
			to play on
			hpos, The int of the handPos
			tpos, The int of the tablePos
			capPair, if there are any matches in the capture
			pile with a card in the hand and in the layout
			h, hand index
			t, table index
Algorithm:
			1) Gets the players hand
			2) Checks for any triples in the layout
			3) If it finds any it returns the indexes of
			those cards.
			4) Checks if any cards can be captured to complete any
			pairs in the capture pile
			5) Captures any matches with the stock card in the layout
Assistance Received: None
**********************************************************************/
std::string Cpu::moveSelector(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks) 
{
	std::vector<std::string> cpuHand;
	std::string playPositon;
	std::string handpos, tablepos;
	int hpos, tpos;
	cpuHand = a_player->returnHand();
	playPositon = checkForTriple(a_player, a_table, a_stacks, cpuHand);
	dashedLine();
	if (playPositon.length() == 4)
	{
		handpos = playPositon[0];
		hpos = stoi(handpos);
		std::cout << "CPU chose to play " << cpuHand[hpos] << " and captures cards ";
		for (int i = 1; i < 4; i++)
		{
			tablepos = playPositon[i];
			tpos = stoi(tablepos);
			std::cout << a_table[tpos] << " ";
		}
		std::cout << "\n";
		return playPositon;
	}
	else if (playPositon != " ")
	{
		handpos = playPositon[0];
		tablepos = playPositon[1];
		if (playPositon[2] != NULL)
		{
			tablepos += playPositon[2];
		}
		hpos = stoi(handpos);
		tpos = stoi(tablepos);

		std::cout << "CPU chose to play " << cpuHand[hpos] << " on layout card " << a_table[tpos] << " to capture the triple stack\n";
		return playPositon;
	}
	bool capPair = false;
	int h;
	int t;
	for (unsigned int i = 0; i < cpuHand.size(); i++)
	{
		capPair = isInCapPile(a_player, cpuHand[i][0]);
		for (unsigned int j = 0; j < a_table.size(); j++)
		{
			if (capPair == true && cpuHand[i][0] == a_table[j][0])
			{
				playPositon = std::to_string(i) + std::to_string(j);
				std::cout << "CPU chose to play " << cpuHand[i] << " on layout card " << a_table[j] << " to capture a pair they can combine with a matching pair in capture pile \n";
				return playPositon;
			}
			else if (capPair == false && cpuHand[i][0] == a_table[j][0])
			{
				playPositon = std::to_string(i) + std::to_string(j);
				h = i;
				t = j;
			}
		}
	}
	std::cout << "CPU chose to play " << cpuHand[h] << " on layout card " << a_table[t] << " to capture double stack\n";
	return playPositon;
}

/**********************************************************************
Function Name: checkForTriple
Purpose: Checks the layout for any 3 cards that are the same and 
gets their indexes
Parameters:
		a_player,
		a_table,
		a_stacks,
		a_hand,
Return Value: The indexes of the cards in the layout and the 
hand index, string
Local Variables:
		play, the indexes of the cards in the layout and the
		hand index being played
		count, to keep track of how many cards in the layout
		match the hand card being compared
		i,j, for loop iterators
Algorithm:
			1)
Assistance Received: None
**********************************************************************/
std::string Cpu::checkForTriple(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks, std::vector<std::string> a_hand)
{
	a_hand = a_player->returnHand();
	std::string play;
	int count = 0;
	for (unsigned int i = 0; i < a_hand.size(); i++)
	{
		for (unsigned int j = 0; j < a_table.size(); j++)
		{
			if (a_stacks[j] == 2 && a_hand[i][0] == a_table[j][0])
			{
				play = std::to_string(i) + std::to_string(j);
				return play;
			}
			else if (a_table[j][0] == a_hand[i][0])
			{
				count++;
				foundTrip.push_back(std::to_string(j));
				if (count >= 3)
				{
					play = std::to_string(i) + foundTrip[0] + foundTrip[1] + foundTrip[2];
					return play;
				}
			}
		}
		foundTrip.clear();
		count = 0;
	}
	play = " ";
	return play;
}

/**********************************************************************
Function Name: menu
Purpose: The menu specifically for the computer player
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
Return Value: The users selection, a string
Local Variables:
		None
Algorithm:
			1) Asks the user what they want to do
			2) Returns the input
Assistance Received: None
**********************************************************************/
std::string Cpu::menu(Player* a_player, Player* a_player2, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_round, int a_score1, int a_score2, std::vector<std::string> a_stock, std::string a_next)
{
	do
	{
		dashedLine();
		std::cout << "CPU turn, What would you like to do?\n";
		std::cout << "1.Save Game\n" << "2.Make Move\n" << "3.Quit game\n";
		std::cin >> menuInput;
		if (menuInput == "1")
		{
			std::cout << "Saving\n";
			serialize(a_player,a_player2,a_table,a_stacks, a_round, a_score1, a_score2, a_stock, a_next);
			exit(0);
		}
		else if (menuInput == "2")
		{
			return "play";
		}
		else if (menuInput == "3")
		{
			return "exit";
		}
		else
		{
			std::cout << "Invalid input, please enter a valid one:\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: stockMatchMenu
Purpose: Used for matching the stock cards with cards on the layout
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
		seed, the random seed when the Computer
		has to choose between 2 options on the layout
		i, for loop iterator
Algorithm:
		1) Searches for any '-' seperated 3 stacks
		2) If no 3 stacks are found then randomly choose one of the options
Assistance Received: None
**********************************************************************/
int Cpu::stockMatchMenu(std::vector<int> a_matchList, std::vector<std::string> a_list, std::string a_cardDrawn, int a_stockIndex)
{
	srand(time(NULL));
	unsigned seed = rand() % (a_matchList.size());
	std::cout << "Computer deciding which card on layout to pair with stock card...\n";
	for (unsigned int i = 0; i < a_matchList.size(); i++)
	{
		if (a_list[a_matchList[i]][2] == '-')
		{
			std::cout << "The Computer used the stock card to a pair on the layout with " << a_cardDrawn << " and " << a_list[a_matchList[i]] << "\n";
			a_stockIndex = a_matchList[i];
			return a_stockIndex;
		}
	}
	std::cout << "The Computer used the stock card to a pair on the layout with " << a_cardDrawn << " and " << a_list[a_matchList[seed]] << "\n";
	a_stockIndex = a_matchList[seed];
	return a_stockIndex;
}
