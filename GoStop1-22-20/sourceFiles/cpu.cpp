#include "cpu.h"


Cpu::~Cpu()
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
std::string Cpu::playTurn(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks, int a_tableCount, int a_stackCount)
{
	std::string tempCard, tempTable;
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
std::string Cpu::moveSelector(Player* a_player, std::vector<std::string> a_table, std::vector <int> a_stacks) //selects the card the CPU will play
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
