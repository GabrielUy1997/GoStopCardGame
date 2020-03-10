#include "round.h"
Round::Round()
{
	starter = 0;
	hand = 0;
	index = 0;
	stockMatchIndex = 0;
	winner = 0;
	tableCounter = 8;
	stackCounter = 8;
	cardsStacking = 0;
	score1 = 0;
	score2 = 0;
	tableStacks = std::vector<int>(tableCounter,0);
}

Round::~Round()
{

}

/**********************************************************************
Function Name: startRound
Purpose: The function that initatiates rounds whether its a new or loaded and calls the 
functions needed to run a single round
Parameters:
		a_player1, pointer to Player obj. Used to represent the Human player
		a_player2, pointer to Player obj. Used to represent the Computer player
		roundCounter, int. Used to denote what round the current game is in
		a_lastWin, int. If it is past the first round of the game it is used to 
		know who won the last round
		a_p1Score, int. Used to know what the score of the Human player is
		a_p2Score, int Used to know what the score of the Computer player is
		a_isNew, bool. Used to know whether the round is the first round of the game
		or not
		a_loadedLay, vector of strings. Used if a game is loaded in and sets the 
		layout to match the file
Return Value: exit type, int
Local Variables:
		exit, string to store whether the player selected exit
Algorithm:
		1) Load in both players scores
		2) Create the dealer object
		3) If it is a new game then set up a new game
		4) If its a loaded game then load the deck from
		the file
		5) If starter is equal to 1 then start the round with
		the human player going first
		6) If starter is equal to 2 then start the round with
		the Computer going first
		7) If starter is 0, then the game must reset because 
		both player have the same hand
		8) If the game was loaded then load the players scores
		9) Determine the winner and display the scores
		10) Return the winner
Assistance Received: None
**********************************************************************/
int Round::startRound(Player* a_player1, Player* a_player2, Player* a_player3, int roundCounter, int a_lastWin, int a_p1Score, int a_p2Score, bool a_isNew, std::vector<std::string> a_loadedLay)
{
	score1 = a_player1->loadScore(a_p1Score);
	score2 = a_player2->loadScore(a_p2Score);
	dashedLine();
	Dealer deal;
	//deal.printDeck();
	if (a_isNew == true)
	{
		deal = passOutCards(deal, a_player1, a_player2);
		starter = goFirst(a_player1, a_player2, a_lastWin);
	}
	else if (a_isNew == false)
	{
		deal.loadDeck(a_loadedLay);
	}
	bool legal = false;
	std::string exit;
	//player1 aka human had priority
	if (starter == 1) 
	{
		do
		{
			//if player selected exit in the player menu
			if (p1Starts(a_player1, a_player2, roundCounter, exit, legal, &deal) == -1) 
			{
				return -1;
			}
		} while (a_player1->returnHand().size() > 0 || a_player2->returnHand().size() > 0);
		showStats(a_player1, a_player2, roundCounter);
		std::cout << "\n";
	}
	//player 2 aka CPU had priority, same as the above if statement but cpu goes first
	else if (starter == 2)
	{
		do
		{
			if (p2Starts(a_player1, a_player2, roundCounter, exit, legal, &deal) == -1)
			{
				return -1;
			}
		} while (a_player2->returnHand().size() > 0 || a_player1->returnHand().size() > 0);
		showStats(a_player1, a_player2, roundCounter);
		std::cout << "\n";
	}
	else if (starter == 0)
	{
		std::cout << "Both players had the same hand so the game needs to reset!\n";
	}
	else
	{
		errorCatch();
	}
	if (a_isNew == false)
	{
		a_player1->loadRoundScore();
		a_player2->loadRoundScore();
	}
	winner = roundEnd(a_player1, a_player2);
	a_p1Score = a_player1->showScore();
	a_p2Score = a_player2->showScore();
	return winner;
}

/**********************************************************************
Function Name: loadRound
Purpose: Loads the data from the load file given into the round variables
Parameters:
		a_player1, pointer to Player obj. Used to represent the Human player
		a_player2, pointer to Player obj. Used to represent the Computer player
		a_nextplayer, int. Used to know who is turn it was when the state of the game
		was saved
		a_layout, vector of strings. The layout from the loaded file
		a_stacks, vector of ints. stacks on the layout from the loaded file
Return Value:
Local Variables:
		None
Algorithm:
		1) If the number is 1 then Human player goes first 
		2) if the number is 2 then Computer player goes first
		3) Set the table cards and the stacks to match the file
		that was loaded
Assistance Received: None
**********************************************************************/
int Round::loadRound(Player* a_player1, Player* a_player2, int a_nextPlayer, std::vector<std::string> a_layout, std::vector<int> a_stacks)
{
	if (a_nextPlayer == 1)
	{
		starter = 1;
	}
	else if (a_nextPlayer == 2)
	{
		starter = 2;
	}
	tableCounter = a_layout.size();
	tableCards = a_layout;
	tableStacks = a_stacks;
	stackCounter = tableStacks.size();
	return 0;
}

/**********************************************************************
Function Name: goFirst
Purpose: Used to determine who goes first either based on who won the previous round or if there is a 
tie/is a new game determines it using the players face cards.
Parameters:
		a_player1, pointer to a Player obj. Used to represent the Human player and check
		if they have the highest card value
		a_player2, pointer to a Player obj. Used to represent the Computer player and check
		if they have the highest card value
		a_lastWin, int passed by value. Used to see who had the most points from the previous
		round
Return Value: The player that is going first in the round, int
Local Variables:
		p1Prior, vector of ints that are used to show what card values the Human player has
		p2Prior, vector of ints that are used to show what card values the Computer player has
Algorithm:
		1) If it isnt the first round then the player that scored the most points the previous
		round goes first
		2) If the previous round was a tie or it is a new game then the player with the highest
		value card gets to go first and their player number is returned
Assistance Received: None
**********************************************************************/
int Round::goFirst(Player* a_player1, Player* a_player2, int a_lastWin)
{
	if (a_lastWin == 1)
	{
		std::cout << "Player got the most points last round so he gets to go first!\n";
		return 1;
	}
	else if (a_lastWin == 2)
	{
		std::cout << "Computer got the most points last round so he gets to go first!\n";
		return 2;
	}
	else
	{
		if (a_lastWin == 3)
		{
			std::cout << "Last round was a tie so who ever has the highest face goes first!\n";
		}
		std::vector<int> p1Prior;
		std::vector<int> p2Prior;
		//returning the values of each card in p1's hand 
		p1Prior = a_player1->faceCards();
		//returning the values of each card in p2's hand
		p2Prior = a_player2->faceCards(); 
		std::cout << "Determining who goes first...\n";
		for (int i = 13; i > 1; i--)
		{
			switch (i)
			{
			case 13:
				std::cout << "K:";
				break;
			case 12:
				std::cout << "Q:";
				break;
			case 11:
				std::cout << "J:";
				break;
			case 10:
				std::cout << "X:";
				break;
			default:
				if (i == 1)
				{
					std::cout << "A:";
				}
				else
				{
					std::cout << i << ":";
				}
			}
			if (p1Prior[i] > p2Prior[i])
			{
				std::cout << p1Prior[i] << " " << p2Prior[i] << "\n";
				std::cout << "Player goes first!\n";
				return 1;
			}
			else if (p1Prior[i] < p2Prior[i])
			{
				std::cout << p1Prior[i] << " " << p2Prior[i] << "\n";
				std::cout << "Computer goes first!\n";
				return 2;
			}
			else if (p1Prior[i] == p2Prior[i])
			{
				std::cout << p1Prior[i] << " " << p2Prior[i] << "\n";
				int value = i;
				switch (value)
				{
				case 13:
					std::cout << "Tie for card " << "K" << "\n";
					break;
				case 12:
					std::cout << "Tie for card " << "Q" << "\n";
					break;
				case 11:
					std::cout << "Tie for card " << "J" << "\n";
					break;
				case 10:
					std::cout << "Tie for card " << "X" << "\n";
					break;
				default:
					if (i == 1)
					{
						std::cout << "Tie for card " << "A" << "\n";
						std::cout << "RESET";
						return 0;
						//reset the game
					}
					std::cout << "Tie for card " << i << "\n";
				}
			}
			else
			{
				std::cout << "ERROR";
				exit(EXIT_FAILURE);
				//reset the game
			}
		}
		errorCatch();
		return 0;
	}
}

/**********************************************************************
Function Name: showTable
Purpose: Displays the layout cards
Parameters:
		None
Return Value: None
Local Variables:
		i, int for loop counter
Algorithm:
		1) Prints out all the cards in the layout
Assistance Received: None
**********************************************************************/
void Round::showTable()
{
	std::cout << "Layout cards: ";
	for (int i = 0; i < tableCounter; i++)
	{
		std::cout << "[" << i + 1 << "] ";
		std::cout << tableCards[i] << " ";
	}
	std::cout << "\n";
}

/**********************************************************************
Function Name: passOutCards
Purpose: Deals the cards to each player and the layout
Parameters:
		a_dealer, Dealer obj. Used to access the deck
		a_player1, pointer to a Player obj. Used to represent the Human player and 
		to give them the hand cards.
		a_player2, pointer to a Player obj. Used to represent the Computer player and 
		to give them the hand cards.
Return Value: the dealer, Dealer obj
Local Variables:
		i, int round counter
Algorithm:
		1) Passes the cards out to both players and the layout in the 
		order specified by the project.
		2) Calls checkIfSameHand to make sure both player dont have the
		same cards
		3) Returns the dealer obj
Assistance Received: None
**********************************************************************/
Dealer Round::passOutCards(Dealer a_dealer, Player* a_player1, Player* a_player2)
{
	//dealing the cards in the specified order 5-5-4-5-5-4
	for (int i = 0; i < 28; i++) 
	{
		if (i < 5)
		{
			cardDrawn = a_dealer.dealCard();
			a_player1->receiveCard(cardDrawn);
		}
		else if (i > 5 && i <= 10)
		{
			cardDrawn = a_dealer.dealCard();
			a_player2->receiveCard(cardDrawn);
		}
		else if (i > 10 && i <= 14)
		{
			cardDrawn = a_dealer.dealCard();
			tableCards.push_back(cardDrawn);
		}
		else if (i > 14 && i <= 19)
		{
			cardDrawn = a_dealer.dealCard();
			a_player1->receiveCard(cardDrawn);
		}
		else if (i > 19 && i <= 24)
		{
			cardDrawn = a_dealer.dealCard();
			a_player2->receiveCard(cardDrawn);
		}
		else
		{
			cardDrawn = a_dealer.dealCard();
			tableCards.push_back(cardDrawn);
		}
	}
	checkIfSameHand(a_dealer, a_player1, a_player2);
	return a_dealer;
}

/**********************************************************************
Function Name: isLegal
Purpose: Determines if the move made by the player is a legal move
Parameters:
		a_playerCard, string passed by value. Used to compare to the table card selected
		a_tableCard, string passed by value. Used to compare to the card played by the player
Return Value: Whether its a legal play or not, bool
Local Variables:
		None
Algorithm:
		1) Checks if the card played from the hand is the same as the table card selected, if
		they have the same value then it is a legal play, returns true;
		2) If the cards arent the same value then it is an illegal move,
		returns false;
Assistance Received: None
**********************************************************************/
bool Round::isLegal(std::string a_playerCard, std::string a_tableCard) //verifying if chosen move is legal
{
	//if values are equal then its a legal play
	if (a_playerCard[0] == a_tableCard[0]) 
	{
		return true;
	}
	else
	{
		std::cout << "Invalid move, try again\n";
		return false;
	}
}

/**********************************************************************
Function Name: stacksOperations
Purpose: Preforms the stacking operations for the layout cards, such as removing cards or
creating 3 stacks 
Parameters:
		a_card, string passed by value. Used to know what card was played
		a_stock, string passed by value. Used to know what stock card was pulled
		a_index, int passed by value. Index of the card selected on the layout
		a_player, pointer to Player obj. Current player
		stackNum, int passed by value. Used to determine if there is a 3 stack on the
		layout index selected
Return Value: None
Local Variables:
		capType, string that represents the value of the card that was passed in
		temp, string that temporarily holds the index of the card currently being used
Algorithm:
		1) Gets the value of the card played from the players hand
		2) Checks if the stock card and the card played match 2 cards in the layout
		3) Checks if there were 3 of the same card were detected in the layout,
		if there was then a full stack is created and added to the current players
		capture pile. Then each one is removed from the layout
		4) If the tableStacks of the index chosen is 2 then the player is playing 
		on a triple stack and they capture a full stack. The full stack is added to
		their capture pile then removed from the layout
		5) If the stackNum is 1 then the player is capturing a half stack, the card
		is then removed from the layout and the half stack is added to the capture
		pile
		6) If it did not fit the criteria of any of the previous steps then
		a 3 stack is created on the layout
Assistance Received: None
**********************************************************************/
void Round::stacksOperatons(std::string a_card, std::string a_stock, int a_index, Player* a_player, int stackNum) 
{
	std::string capType;
	capType = a_card;
	if (threeInLay == true)
	{
		std::cout << "Full stack created, you get a point!\n";
		a_player->addCapture(capType, tableCards[a_index], 4, threeInLay, threeStack);
		std::cout << "added to capture pile\n";
		std::string temp;
		//If there are 2 matches in the layout and the the stock card matches the played card
		if (stockCap3 == true)
		{
			int j = 0;
			for (int i = 1; i < 3; i++)
			{
				temp = play[i];
				a_index = stoi(temp);
				if (i > 1)
				{
					a_index -= j;
				}
				tableCards.erase(tableCards.begin() + a_index);
				tableStacks.erase(tableStacks.begin() + a_index);
				tableCounter--;
				stackCounter--;
				j++;
			}
		}
		//capturing 3 cards from the layout
		else
		{
			int k = 0;
			for (int i = 1; i < 4; i++)
			{
				temp = play[i];
				a_index = stoi(temp);
				if (i > 1)
				{
					a_index -= k;
				}
				tableCards.erase(tableCards.begin() + a_index);
				tableStacks.erase(tableStacks.begin() + a_index);
				tableCounter--;
				stackCounter--;
				k++;
			}
		}
	}
	//if a 3 stack was completed
	else if (tableStacks[a_index] == 2)
	{
		std::cout << "Full stack created, you get a point!\n";
		a_player->addCapture(capType, tableCards[a_index] , 4, threeInLay, threeStack);
		std::cout << " added to capture pile\n";
		tableCards.erase(tableCards.begin() + a_index);
		tableStacks.erase(tableStacks.begin() + a_index);
		tableCounter--;
		stackCounter--;
	}
	//if a normal pair was captured
	else if (stackNum == 1)
	{
		std::cout << "Half stack captured!\n";
		a_player->addCapture(capType, tableCards[a_index], 2, threeInLay, threeStack);
		std::cout << " added to capture pile\n";
		if (addToLay == false || stackNum == 2)
		{
			tableCards.erase(tableCards.begin() + a_index);
			tableStacks.erase(tableStacks.begin() + a_index);
			tableCounter--;
			stackCounter--;
		}
	}
	else
	{
		std::cout << "3 stack created\n";
		tableCards[a_index] += "-" + a_card + "-" + a_stock;
		++++tableStacks[a_index];
	}
	threeInLay = false;
	stockCap3 = false;
	threeStack = " ";
}

/**********************************************************************
Function Name: addToLayout
Purpose: Used to add cards to the layout
Parameters:
		a_play, string passed by value. Used to add to the layout
Return Value: None
Local Variables: 
		None
Algorithm:
		1) Insert the card passed in to the tableCards vector
		2) Insert another index to the tableStacks vector to 
		keep track of if it is stacked or not
		3) Increment tableCounter and stacksCounter
		4) Display to the screen what card is being added to the layout
Assistance Received: None
**********************************************************************/
void Round::addToLayout(std::string a_play)
{
	tableCards.insert(tableCards.begin() + tableCounter, a_play);
	tableStacks.insert(tableStacks.begin() + stackCounter, 0);
	tableCounter++;
	stackCounter++;
	std::cout << "Adding card " << a_play << " to layout\n";
}

/**********************************************************************
Function Name: playStock
Purpose: Draws the stock card and checks if the card makes a triple stack
Parameters:
		a_deal, Dealer obj. Used to access the deck
		a_cardsStacking, int passed by value. Used to set triple stacks if
		cards match
Return Value: a_dealer, Dealer object passed by value
Local Variables:
		None
Algorithm:
		1) Pulls the card from the top of the stockpile
		2) Displays the card
		3) Checks if the card matches the card the current player is playing
		from their hand
		4) Return the updated dealer obj
Assistance Received: None
**********************************************************************/
Dealer Round::playStock(Dealer a_deal, int a_cardsStacking)
{
	//pulling the stock card from the stockpile
	cardDrawn = a_deal.dealCard(); 
	std::cout << "The stock card played is:" << cardDrawn << "\n";
	//if the stock card is the same as played then stack 2
	if (cardDrawn[0] == p_cardChosen[0]) 
	{
		cardsStacking = 2;
	}
	else
	{
		cardsStacking = 1;
	}
	return a_deal;
}

/**********************************************************************
Function Name: showStats
Purpose: Displays the hand and capture piles of both players and the layout
Parameters:
		a_player1, pointer to a Player obj. Used to represent the Human player
		a_player2, pointer to a Player obj. Used to represent the Computer player
		a_roundCounter, int passed by value. Used to display the current round
Return Value: None
Local Variables:
		None
Algorithm:
		1) Print round, both players hands and capture piles, and score
Assistance Received: None
**********************************************************************/
void Round::showStats(Player* a_player1, Player* a_player2, int a_roundCounter)
{
	dashedLine();
	std::cout << "Round:" << a_roundCounter << "\n";
	std::cout << "Computer:\n";
	std::cout << "\tComputer score is " << score2 << "\n";
	std::cout << "\tHand: ";
	a_player2->showHand();
	std::cout << "\t";
	a_player2->showCapturePile();
	std::cout << "\n";
	std::cout << "Player:\n";
	std::cout << "\tPlayer score is " << score1 << "\n";
	std::cout << "\tHand: ";
	a_player1->showHand();
	std::cout << "\t";
	a_player1->showCapturePile();
	std::cout << "\n";
	showTable();
	std::cout << "Next card in deck is: ";
}


/**********************************************************************
Function Name: roundEnd
Purpose: Displays the results of a round after it ends
Parameters:
		a_player1, pointer to a Player obj. Used to represent the Human player
		a_player2, pointer to a Player obj. Used to represent the Computer player
Return Value: The winner, 1 for player 1, 2 for player2, or 3 for tie, an int
Local Variables:
		None
Algorithm:
		1) Shows that a round has ended
		2) Prints both players scores during the round and total game score after
		recieving the points
		3) Returns the winner
Assistance Received: None
**********************************************************************/
int Round::roundEnd(Player* a_player1, Player* a_player2)
{
	dashedLine();
	std::cout << "Round complete! Giving points out now!\n";
	score1 = a_player1->showScore();
	std::cout << "Player score is now: " << score1 << " after gaining " << a_player1->returnRoundScore() <<  " points\n";
	score2 = a_player2->showScore();
	std::cout << "Computer score is now: " << score2 << " after gaining " << a_player2->returnRoundScore() << " points\n";
	if (a_player1->returnRoundScore() > a_player2->returnRoundScore())
	{
		return 1;
	}
	else if (a_player1->returnRoundScore() < a_player2->returnRoundScore())
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

/**********************************************************************
Function Name: errorCatch
Purpose: Used if incorrect inputs are entered
Parameters:
		None
Return Value: None
Local Variables:
		None
Algorithm:
		1) Used to tell if somehow an incorrect input was taken
Assistance Received: None
**********************************************************************/
void Round::errorCatch()
{
	std::cout << "ERROR";
	exit(EXIT_FAILURE);
}

/**********************************************************************
Function Name: noPlay
Purpose: Used when a player has no matches to make on the layout
Parameters:
		a_player, pointer to Player obj. Used to know what player is currently playing
Return Value: None
Local Variables:
		None
Algorithm:
		1) Get the index of the card that the player wants to add to the layout
		2) Pull it from the players hand
Assistance Received: None
**********************************************************************/
void Round::noPlay(Player* a_player)
{
	//hand index
	tempCard = play[0];
	hand = stoi(tempCard);
	p_cardChosen = a_player->pullCard(hand);
}

/**********************************************************************
Function Name: canPlay
Purpose: Used when the player does have a possible play on the layout
Parameters:
		a_player, pointer to a Player obj. Used to know what player is currently playing
Return Value: None
Local Variables:
		None
Algorithm:
		1) Gets the index of the card the player wants to play from their hand
		2) Checks if the string's second index is empty then the table cards index
		is less than 10, if it isnt empty then make sure the second digit of the
		index isnt cut off
		3) Use the indexes to get the card from the players hand and the card 
		on the layout
Assistance Received: None
**********************************************************************/
void Round::canPlay(Player* a_player)
{
	//hand index selected
	tempCard = play[0];
	//if the index of the card is less than 10
	if (play[2] == NULL)
	{
		//table index
		tempTable = play[1];
	}
	//if the index of the table card is double digits
	else
	{
		tempTable = "";
		//table indexes
		tempTable += play[1];
		tempTable += play[2];
	}
	hand = stoi(tempCard);
	index = stoi(tempTable);
	//gets the actual card from the hand using the index
	p_cardChosen = a_player->pullCard(hand);
	//gets the actual card from the table
	p_tableChosen = tableCards[index];
}


/**********************************************************************
Function Name: checkStacks
Purpose: Used to check whether there is a triple or a pair being created in the layout
Parameters:
		a_player, pointer to a Player obj. Used to know what player is currently playing
Return Value: None
Local Variables:
		tableMatches[], a vector of ints that holds the
		index of the each card that matches the card played 
Algorithm:
		1) Checks if it is possible to play a card and capture 3 layout cards,
		if not then it is still possible card can be added to the layout
		2) Checks if the card played is the same as the stock card, if it is
		then stack them meaning that it will make a 3 stack, if the stock card
		does match the card played check if they can capture 2 cards that match 
		in the layout
		3) If the stock and played card arent the same then 3 stack isnt created
		4) If the card that was played isnt being added to the layout then continue
		and call the stacksOperations function
		5) If the stock card didnt match the card played or the card played collected
		3 cards on the layout then search the layout for matches with the stock card
		6) Add the index of each match to the tableMatches vector, if there are no 
		matches then addToLay is still true
		7) If there is only one match then it prints out what kind of capture it is
		and captures the card that is at that index on the layout
		8) If ther is more than one match then it calls the current players stockMatchMenu
		and uses the value that is returned
		9) If the stock card had no matches then it is added to the layout
		10) If the stock card had one or more matches then the stacksOperations function
		is called
Assistance Received: None
**********************************************************************/
void Round::checkStacks(Player* a_player)
{
	std::vector<int> tableMatches;
	//if threeInLay is true there are 3 cards in the layout that matches a playable card
	if (threeInLay == true)
	{
		addToLay = false;
	}
	//if the stock card is the same as played then stack 2
	else if ((cardDrawn[0] == p_cardChosen[0]) && (addToLay == false)) 
	{
		cardsStacking = 2;
	}
	else
	{
		cardsStacking = 1;
	}
	//if player card isnt being added to layout
	if (addToLay == false) 
	{
		for (unsigned int i = 0; i < tableCards.size(); i++)
		{
			if (cardDrawn[0] == tableCards[i][0])
			{
				tableMatches.push_back(i);
			}
		}
		if (cardsStacking == 2 && tableMatches.size() == 2)
		{
			std::cout << "The stock card " << cardDrawn << " matches the card played and 2 cards on the layout: " << p_cardChosen << " " << tableCards[tableMatches[0]] << " " << tableCards[tableMatches[1]] << "\n";
			threeStack = cardDrawn + " " + tableCards[tableMatches[1]] + " ";
			play = play + std::to_string(tableMatches[1]);
			threeInLay = true;
			stockCap3 = true;
		}
		stacksOperatons(p_cardChosen, cardDrawn, index, a_player, cardsStacking);
		tableMatches.clear();
	}
	//getting the indexes of all the matches with the stock card on the layout
	if (cardsStacking == 1 || cardsStacking == 0)
	{
		for (unsigned int i = 0; i < tableCards.size(); i++)
		{
			if (cardDrawn[0] == tableCards[i][0])
			{
				tableMatches.push_back(i);
			}
			else
			{
				addToLay = true;
			}
		}
	}
	//if there is only one match
	if (tableMatches.size() == 1 && cardsStacking != 2)
	{
		addToLay = false;
		//if completeing a 3 stack
		if (cardsStacking == 2)
		{
			std::cout << "The stock card completed a triple stack on the layout with " << cardDrawn << " and " << tableCards[tableMatches[0]] << "\n";
		}
		else
		{
			cardsStacking = 1;
			std::cout << "The stock card created a pair on the layout with " << cardDrawn << " and " << tableCards[tableMatches[0]] << "\n";
		}
		stockMatchIndex = tableMatches[0];
	}
	//if there is more than one match
	else if (tableMatches.size() >= 2 && cardsStacking != 2)
	{
		addToLay = false;
		stockMatchIndex = a_player->stockMatchMenu(tableMatches, tableCards, cardDrawn, stockMatchIndex);

	}
	//if the stock card doesnt have a match add it to the layout
	if (cardsStacking == 1 && addToLay == true || cardsStacking == 0 && addToLay == true) 
	{
		addToLayout(cardDrawn);
	}
	//if the stock card does have a match
	else if ((cardsStacking == 1 && addToLay == false) || (cardsStacking == 2 && addToLay == true) || cardsStacking == 0)
	{
		stacksOperatons(cardDrawn, cardDrawn, stockMatchIndex, a_player, cardsStacking);
	}
}


/**********************************************************************
Function Name: checkIfSameHand
Purpose: Used to check if both players have duplicate hands
Parameters:
		a_dealer, Dealer obj. Used to access the deck
		a_player1, pointer to a Player obj. Used to represent the Human player
		a_player2, pointer to a Player obj. Used to represent the Computer player
Return Value: None
Local Variables:
		p1_hand, vector of strings that holds the Human players hand
		p2_hand, vector of strings that holds the CPU players hand
		reset, bool that is used to know if players have the same hand
		i, int for loop counter
		j, int for loop counter
Algorithm:
		1) Gets the hands of both players
		2) Checks if both players have the same hand
		3) If they arent the same return and do nothing
		4) If they are the same, call the dealer deconstructor,
		clear both players hands, create a new dealer obj, and pass
		out the cards again
Assistance Received: None
**********************************************************************/
void Round::checkIfSameHand(Dealer a_dealer, Player* a_player1, Player*a_player2)
{
	std::vector<std::string> p1_hand = a_player1->returnHand();
	std::vector<std::string> p2_hand = a_player2->returnHand();
	bool reset;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (p1_hand[i] == p2_hand[j])
			{
				reset = true;
				break;
			}
			else
			{
				reset = false;
			}
		}
		if (reset == false)
		{
			std::cout << "Not same hand\n";
			return;
		}
	}
	std::cout << "Same hand, resetting hands and deck so dealer can deal new cards\n";
	a_dealer.~Dealer();
	a_player1->clearHand();
	a_player2->clearHand();
	Dealer deal;
	passOutCards(deal, a_player1, a_player2);
}


/**********************************************************************
Function Name: p1Starts
Purpose: Used when the human player is determined the starter and calls operations that
are used by the players to play the round
Parameters:
		a_player1, pointer to a Player obj. Used to represent the Human player
		a_player2, pointer to a Player obj. Used to represent the Computer player
		roundCounter, int passed by value. Used to display what round is currently being
		played
		a_exit, string passed by value. Used to know if the player chose to exit the game
		a_legal, bool passed by value. Used to denote if the play made was legal
		a_deal, pointer to a Dealer obj. Used to access the deck
Return Value: The type of exit from the round, if the player exited or the round
finished normally, int.
Local Variables:
		None
Algorithm:
		1) Show the layout, hands, capture piles, and next card
		2) Brings up the player menu for the Human player
		3) Calls the Human play function
		4) Checks if the play the Human chose was either adding to the layout,
		capturing three cards off the layout, or a regular pair capture
		5) Calls function that removes the card from the Human player's hand
		6) Calls function that draws the card at the top of the stock pile
		and prints it to the screen
		7) Calls function that checks if the stock card creates a stack, 
		3 stack, or if it gets added to the layout
		8) Checks if the CPU player still has cards in his hand,
		if not end the round, else continue through to the CPUs turn
		9) Show the layout, hands, capture piles, and next card
		10) Brings up the player menu for the CPU player
		11) Calls the CPU play function
		12) Checks if the play the CPU chose was either adding to the layout,
		capturing three cards off the layout, or a regular pair capture
		13) Calls function that removes the card from the CPU player's hand
		14) Calls function that draws the card at the top of the stock pile
		and prints it to the screen
		15) Calls function that checks if the stock card creates a stack, 
		3 stack, or if it gets added to the layout
Assistance Received: None
**********************************************************************/
int Round::p1Starts(Player* a_player1, Player* a_player2, int roundCounter, std::string a_exit, bool a_legal, Dealer* a_deal)
{
	showStats(a_player1, a_player2, roundCounter);
	a_deal->topCard();
	nextPlayer = "Computer";
	std::cout << "Next player is: " << nextPlayer << "\n";
	do
	{
		a_exit = a_player1->menu(a_player1, a_player2, tableCards, tableStacks, roundCounter, score1, score2, a_deal->returnDeck(), nextPlayer);
		if (a_exit == "exit")
		{
			return -1;
		}
		else if (a_exit == "help")
		{
			a_player1->helpMenu(a_player1, tableCards, tableStacks);
		}
		//returns the index of the card the player wants to play in the hand and the index of the layout they want to play to
		play = a_player1->playTurn(a_player1, tableCards, tableStacks, tableCounter, stackCounter);
		if (play[0] == 'x')
		{
			std::cout << "Invalid play\n";
		}
		//if there was no possible play for the player
		else if (play[1] == NULL)
		{
			noPlay(a_player1);
			addToLayout(p_cardChosen);
			addToLay = true;
			break;
		}
		//capturing 3 cards in the layout
		else if (play.length() == 4)
		{
			tripleLayoutCap(a_player1);
			std::cout << "Player playing " << p_cardChosen << " on layout card " << p_tableChosen << "\n";
			addToLay = false;
			a_legal = isLegal(p_cardChosen, p_tableChosen);
		}
		else
		{
			canPlay(a_player1);
			dashedLine();
			std::cout << "Player playing " << p_cardChosen << " on layout card " << p_tableChosen << "\n";
			addToLay = false;
			a_legal = isLegal(p_cardChosen, p_tableChosen);
		}
	} while (a_legal == false);
	//removes card from players hand after verification
	a_player1->removeCard(hand); 
	//pulling the stock card from the stockpile
	cardDrawn = a_deal->dealCard();
	std::cout << "The stock Card played is:" << cardDrawn << "\n";
	checkStacks(a_player1);
	if (a_player2->returnHand().size() == 0)
	{
		return 1;
	}
	//start p2 turn
	showStats(a_player1, a_player2, roundCounter);
	a_deal->topCard();
	nextPlayer = "Human";
	std::cout << "Next player is: " << nextPlayer << "\n";
	a_exit = a_player2->menu(a_player1, a_player2, tableCards, tableStacks, roundCounter, score1, score2, a_deal->returnDeck(), nextPlayer);
	if (a_exit == "exit")
	{
		return -1;
	}
	play = a_player2->playTurn(a_player2, tableCards, tableStacks, tableCounter, stackCounter);
	//if there was no possible play for the player
	if (play[1] == NULL)
	{
		dashedLine();
		noPlay(a_player2);
		std::cout << "CPU chose to play " << p_cardChosen << " to layout becuase no play available\n";
		addToLayout(p_cardChosen);
		addToLay = true;
		threeInLay = false;
	}
	//capturing 3 cards in the layout
	else if (play.length() == 4)
	{
		tripleLayoutCap(a_player2);
		addToLay = false;
	}
	else
	{
		canPlay(a_player2);
		addToLay = false;
		threeInLay = false;
	}
	a_player2->removeCard(hand);
	//pulling the stock card from the stockpile
	cardDrawn = a_deal->dealCard(); 
	std::cout << "The stock Card played is:" << cardDrawn << "\n";
	checkStacks(a_player2);
}

/**********************************************************************
Function Name: p2Starts
Purpose: Used when computer player is determined the starter
Parameters:
		a_player1, pointer to a Player obj. Used to represent the Human player
		a_player2, pointer to a Player obj. Used to represent the Computer player
		roundCounter, int passed by value. Used to display what round is currently being
		played
		a_exit, string passed by value. Used to know if the player chose to exit the game
		a_legal, bool passed by value. Used to denote if the play made was legal
		a_deal, pointer to a Dealer obj. Used to access the deck
Return Value: The type of exit from the round, if the player exited or the round
finished normally, int.
Local Variables:
		None
Algorithm:
		1) Show the layout, hands, capture piles, and next card
		2) Brings up the player menu for the CPU player
		3) Calls the CPU play function
		4) Checks if the play the CPU chose was either adding to the layout,
		capturing three cards off the layout, or a regular pair capture
		5) Calls function that removes the card from the CPU player's hand
		6) Calls function that draws the card at the top of the stock pile
		and prints it to the screen
		7) Calls function that checks if the stock card creates a stack, 
		3 stack, or if it gets added to the layout
		8) Checks if the Human player still has cards in his hand,
		if not end the round, else continue through to the Humans turn
		9) Show the layout, hands, capture piles, and next card
		10) Brings up the player menu for the Human player
		11) Calls the Human play function
		12) Checks if the play the Human chose was either adding to the layout,
		capturing three cards off the layout, or a regular pair capture
		13) Calls function that removes the card from the Human player's hand
		14) Calls function that draws the card at the top of the stock pile
		and prints it to the screen
		15) Calls function that checks if the stock card creates a stack, 
		3 stack, or if it gets added to the layout
Assistance Received: None
**********************************************************************/
int Round::p2Starts(Player* a_player1, Player* a_player2, int roundCounter, std::string a_exit, bool a_legal, Dealer* a_deal)
{
	showStats(a_player1, a_player2, roundCounter);
	a_deal->topCard();
	nextPlayer = "Human";
	std::cout << "Next player is: " << nextPlayer << "\n";
	a_exit = a_player2->menu(a_player1, a_player2, tableCards, tableStacks, roundCounter, score1, score2, a_deal->returnDeck(), nextPlayer);
	if (a_exit == "exit")
	{
		return -1;
	}
	play = a_player2->playTurn(a_player2, tableCards, tableStacks, tableCounter, stackCounter);
	//if there was no possible play for the player
	if (play[1] == NULL)
	{
		dashedLine();
		noPlay(a_player2);
		std::cout << "CPU chose to play " << p_cardChosen << " to layout becuase no play available\n";
		addToLayout(p_cardChosen);
		addToLay = true;
	}
	//capturing 3 cards in the layout
	else if (play.length() == 4)
	{
		tripleLayoutCap(a_player2);
		addToLay = false;
	}
	else
	{
		canPlay(a_player2);
		addToLay = false;
	}
	a_player2->removeCard(hand);
	//pulling the stock card from the stockpile
	cardDrawn = a_deal->dealCard();
	std::cout << "The stock Card played is:" << cardDrawn << "\n";
	checkStacks(a_player2);
	if (a_player1->returnHand().size() == 0)
	{
		return 1;
	}
	//start p1 turn
	do 
	{
		showStats(a_player1, a_player2, roundCounter);
		a_deal->topCard();
		nextPlayer = "Computer";
		std::cout << "Next player is: " << nextPlayer << "\n";
		a_exit = a_player1->menu(a_player1, a_player2, tableCards, tableStacks, roundCounter, score1, score2, a_deal->returnDeck(), nextPlayer);
		if (a_exit == "exit")
		{
			return -1;
		}
		if (a_exit == "help")
		{
			a_player1->helpMenu(a_player1, tableCards, tableStacks);
		}
		play = a_player1->playTurn(a_player1, tableCards, tableStacks, tableCounter, stackCounter);
		if (play[0] == 'x')
		{
			std::cout << "Invalid play, please follow the help function\n";
		}
		//if there was no possible play for the player
		else if (play[1] == NULL)
		{
			noPlay(a_player1);
			addToLayout(p_cardChosen);
			addToLay = true;
			break;
		}
		//capturing 3 cards in the layout
		else if (play.length() == 4)
		{
			tripleLayoutCap(a_player1);
			std::cout << "Player playing " << p_cardChosen << " on layout card " << p_tableChosen << "\n";
			addToLay = false;
			a_legal = isLegal(p_cardChosen, p_tableChosen);
		}
		else
		{
			canPlay(a_player1);
			dashedLine();
			std::cout << "Player playing " << p_cardChosen << " on layout card " << p_tableChosen << "\n";
			addToLay = false;
			a_legal = isLegal(p_cardChosen, p_tableChosen);
		}
	} while (a_legal == false);
	//removes card from players hand after verification
	a_player1->removeCard(hand);
	//pulling the stock card from the stockpile
	cardDrawn = a_deal->dealCard();
	std::cout << "The stock Card played is:" << cardDrawn << "\n";
	checkStacks(a_player1);
}

/**********************************************************************
Function Name: TripleLayoutCap
Purpose: Used to capture three cards off the layout that arent stacked
Parameters:
		a_player, pointer to a Player obj. Used to access the correct
		players cards
Return Value: None
Local Variables:
		i, int for loop counter
Algorithm:
		1) Appends the second and third matches index to the threeStack string
		2) Gets the card chosen by the player
		3) Gets the layout card chosen by the player
Assistance Received: None
**********************************************************************/
void Round::tripleLayoutCap(Player* a_player)
{
	threeInLay = true;
	threeStack = "";
	//adding the index of the other two matches to the string
	for (int i = 2; i < 4; i++)
	{
		tempTable = play[i];
		index = stoi(tempTable);
		threeStack += tableCards[index] + " ";
	}
	tempCard = play[0];
	tempTable = play[1];
	hand = stoi(tempCard);
	index = stoi(tempTable);
	//gets the actual card from the hand using the index
	p_cardChosen = a_player->pullCard(hand); 
	//gets the layout card at the index chosen
	p_tableChosen = tableCards[index];
}
