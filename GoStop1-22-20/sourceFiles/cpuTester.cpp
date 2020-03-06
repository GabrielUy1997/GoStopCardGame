//else if (starter == 3)
//{
//	for (int a = 0; a < 10; a++)
//	{
//		showStats(a_player2, a_player3, roundCounter);
//		deal.topCard();
//		nextPlayer = "Human";
//		exit = a_player2->menu(a_player2, a_player3, tableCards, tableStacks, roundCounter, score1, score2, deal.returnDeck(), nextPlayer);
//		if (exit == true)
//		{
//			return -1;
//		}
//		play = a_player2->playTurn(a_player2, tableCards, tableStacks, tableCounter, stackCounter);
//		if (play[1] == NULL)
//		{
//			dashedLine();
//			noPlay(a_player2);
//			std::cout << "CPU chose to play " << p_cardChosen << " to layout becuase no play available\n";
//			addToLayout(p_cardChosen);
//			addToLay = true;
//		}
//		else
//		{
//			canPlay(a_player2);
//			addToLay = false;
//			dashedLine();
//			if (play[2] != NULL)
//			{
//				std::cout << "CPU chose to play " << p_cardChosen << " on layout card " << p_tableChosen << " to capture the triple stack\n";
//			}
//			else
//			{
//				std::cout << "CPU chose to play " << p_cardChosen << " on layout card " << p_tableChosen << " to capture double stack\n";
//			}
//		}
//		a_player2->removeCard(hand);
//		cardDrawn = deal.dealCard(); //pulling the stock card from the stockpile
//		std::cout << "The stock Card played is:" << cardDrawn << "\n";
//		checkStacks(a_player2);
//		//player 3
//		showStats(a_player2, a_player3, roundCounter);
//		deal.topCard();
//		nextPlayer = "Human";
//		exit = a_player3->menu(a_player2, a_player3, tableCards, tableStacks, roundCounter, score1, score2, deal.returnDeck(), nextPlayer);
//		if (exit == true)
//		{
//			return -1;
//		}
//		play = a_player3->playTurn(a_player3, tableCards, tableStacks, tableCounter, stackCounter);
//		if (play[1] == NULL)
//		{
//			dashedLine();
//			noPlay(a_player3);
//			std::cout << "CPU chose to play " << p_cardChosen << " to layout becuase no play available\n";
//			addToLayout(p_cardChosen);
//			addToLay = true;
//		}
//		else
//		{
//			canPlay(a_player3);
//			addToLay = false;
//			dashedLine();
//			if (play[2] != NULL)
//			{
//				std::cout << "CPU chose to play " << p_cardChosen << " on layout card " << p_tableChosen << " to capture the triple stack\n";
//			}
//			else
//			{
//				std::cout << "CPU chose to play " << p_cardChosen << " on layout card " << p_tableChosen << " to capture double stack\n";
//			}
//		}
//		a_player3->removeCard(hand);
//		cardDrawn = deal.dealCard(); //pulling the stock card from the stockpile
//		std::cout << "The stock Card played is:" << cardDrawn << "\n";
//		checkStacks(a_player3);
//	}
//}
