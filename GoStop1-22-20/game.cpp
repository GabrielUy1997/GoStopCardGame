#include "game.h"

Game::Game()
{
	playAgain = true;
	newOrLoads = true;
	winner = 0;
	roundCounter = 1;
	playerScore = 0;
	cpuScore = 0;
	loadNextPlayer = 0;
	startGame();
}

Game::~Game()
{

}

/**********************************************************************
Function Name: startGame
Purpose: Starts the game and creates the player objects, the round object,
and deals with load files.
Parameters:
		None
Return Value: None
Local Variables:
		None
Algorithm:
		1) Checks if the game is a loaded file or is a new game
		2) Creates the all the player objects and the round object
		3) If the game is loaded then load all the data from the 
		load file and start the round
		4) If the game is new then it starts a new game
		5) After a round ends it declares the winner of the round,
		shows the scores, and asks if the human would like 
		to play another round
		6) If the player would like to play another then it remakes 
		the objects again and starts the round
		7) If the player wants to quit then it calls the function
		to determine the winner
Assistance Received: None
**********************************************************************/
void Game::startGame()
{
	newOrLoads = newOrLoad();
	do
	{
		Player* p1;
		Player* p2;
		Player* p3;
		Human player1;
		Cpu player2;
		Cpu player3;
		p1 = &player1;
		p2 = &player2;
		p3 = &player3;
		Round startRound;
		if (newOrLoads == false)
		{
			p1->loadGame(loadP1Hand, loadP1Cap, playerScore);
			p2->loadGame(loadP2Hand, loadP2Cap, cpuScore);
			startRound.loadRound(p1, p2, loadNextPlayer, loadLayout, loadStack);
		}
		winner = startRound.startRound(p1, p2, p3, roundCounter, winner, playerScore, cpuScore, newOrLoads, loadStockPile);
		askToPlay(winner);
		playerScore = p1->showScore();
		cpuScore = p2->showScore();
		newOrLoads = true;
	} while (playAgain == true);
	determineWinner();
}

/**********************************************************************
Function Name: askToPlay
Purpose: Menu to ask if the player would like to play another round
Parameters:
		a_winner, int passed by value. Last winner or player exiting the game
Return Value: None
Local Variables:
		valid, bool. Tells if input is valid or not
Algorithm:
		1) If the value passed in through a_winner is -1
		then the player has selected exit in the menu and wants
		to exit the game, it sets playagain to false and returns
		2) If the player didint select exit then it asks if they
		would like to play another round
		3) If the player inputs y then the roundCounter increments 
		and sets playAgain to true, if they input n then playAgain
		is set to false
Assistance Received: None
**********************************************************************/

void Game::askToPlay(int a_winner)
{
	if (a_winner == -1)
	{
		playAgain = false;
		return;
	}
	bool valid;
	do
	{
		std::cout << "Would you like to play another round? (Y/N):";
		std::cin >> choice;
		if (choice == "Y" || choice == "y")
		{
			playAgain = true;
			valid = true;
			roundCounter++;
		}
		else if (choice == "N" || choice == "n")
		{
			playAgain = false;
			valid = true;
		}
		else
		{
			std::cout << "Invalid entry, try again\n";
			valid = false;
		}
	} while (valid == false);

}

/**********************************************************************
Function Name: determineWinner
Purpose: Determines the winner of the game based on the players scores
Parameters:
		None
Return Value: None
Local Variables:
		exit, int. Used to hold the exit
Algorithm:
		1) Decides the winner based on who ever has the highest
		score or declares a tie if they are equal
		2) Asks to enter key to exit
Assistance Received: None
**********************************************************************/
void Game::determineWinner()
{
	std::cout << "Exiting game...\n";
	if (playerScore > cpuScore)
	{
		std::cout << "Player wins the game with " << playerScore << " points!\n";
	}
	else if (playerScore < cpuScore)
	{
		std::cout << "Computer wins the game with " << cpuScore << " points!\n";
	}
	else if (playerScore == cpuScore)
	{
		std::cout << "Player and Computer tie the game with " << playerScore << " points!\n";
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	std::cout << "Thanks for playing!\n";
	int exit;
	std::cout << "Enter any key to exit...";
	std::cin >> exit;
	return;
}

/**********************************************************************
Function Name: newOrLoad
Purpose: Used to have the player input whether it is a new game or load
Parameters:
		None
Return Value: Whether it is a new game or not, bool
Local Variables:
		None
Algorithm:
		1) Asks if player would like a new game or load one
		2) If they input new then return true, if they
		input load then load the game and return false
Assistance Received: None
**********************************************************************/
bool Game::newOrLoad()
{
	do
	{
		std::cout << "New game or would you like to load a previous game? (New/Load): ";
		std::cin >> choice;
		if (choice == "New" || choice == "new")
		{
			return true;
		}
		else if (choice == "Load" || choice == "load")
		{
			loadGame();
			return false;
		}
		else
		{
			std::cout << "Invalid entry, try again\n";
		}
	} while (true);
}

/**********************************************************************
Function Name: loadGame
Purpose: Reading in the load file
Parameters:
		None
Return Value: None
Local Variables:
		file, fstream. fstream to read in the file
		word, string. String to hold each word as it reads through
		the file
		fileName, string. Name of the file the user wants to load
Algorithm:
		1) Asks for the file the user wants to load
		2) Open the file and read the file, take in the data
		and store it into the correct variables
Assistance Received: None
**********************************************************************/
void Game::loadGame()
{
	std::fstream file;
	std::string word, fileName;
	do
	{
		std::cout << "Please input a file name with the extention .txt:";
		std::cin >> fileName;

		size_t found = fileName.find(".txt", (fileName.size() - 4), 4);
		if (found != std::string::npos)
		{
			file.open(fileName.c_str());
			while (file >> word)
			{
				if (word == "Round:")
				{
					file >> word;
					roundCounter = stoi(word);
				}
				if (word == "Computer:")
				{
					do
					{
						if (word == "Score:")
						{
							file >> word;
							cpuScore = stoi(word);
						}
						if (word == "Hand:")
						{
							file >> word;
							while (word != "Capture")
							{
								loadP2Hand.push_back(word);
								file >> word;
							}
						}
						if (word == "Capture")
						{
							file >> word;
							while (word != "Human:")
							{
								file >> word;
								if (word != "Human:")
								{
									loadP2Cap.push_back(word);
								}
							}
						}
						if (word == "Human:")
						{
							file >> word;
							do
							{
								if (word == "Score:")
								{
									file >> word;
									playerScore = stoi(word);
								}
								if (word == "Hand:")
								{
									file >> word;
									while (word != "Capture")
									{
										loadP1Hand.push_back(word);
										file >> word;
									}
								}
								if (word == "Capture")
								{
									file >> word;
									while (word != "Layout:")
									{
										file >> word;
										if (word != "Layout:")
										{
											loadP1Cap.push_back(word);
										}
									}
								}
								if (word == "Layout:")
								{
									file >> word;
									while (word != "Stock")
									{
										loadLayout.push_back(word);
										if (word.length() > 2)
										{
											loadStack.push_back(2);
										}
										else
										{
											loadStack.push_back(0);
										}
										file >> word;
									}
								}
								if (word == "Stock")
								{
									file >> word;
									while (word != "Next")
									{
										file >> word;
										loadStockPile.push_back(word);
									}
								}
								if (word == "Next")
								{
									file >> word;
									file >> word;
									file >> word;
									file >> word;
									if (word == "Human")
									{
										loadNextPlayer = 1;
									}
									else if (word == "Computer")
									{
										loadNextPlayer = 2;
									}
									break;
								}
								file >> word;
							} while (true);
							break;
						}
						file >> word;
					} while (true);
				}
			}
			break;
		}
		else
		{
			std::cout << "invalid file\n";
		}
	} while (true);
}