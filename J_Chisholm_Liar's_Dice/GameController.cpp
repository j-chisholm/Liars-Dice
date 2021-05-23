//The game controller class is responsible for retrieving
//information from the user to determine the flow of the
//program. When the player runs the game, the game controller
//releases controll to the game loop class to play the game.

/*
* MAJOR PROBLEMS:
* 
* When getting the necessary information from the player, I
* was not able to properly get and test player input especially
* if the player entered characters instead of integers. The
* workaround to this was using the clear() and ignore()
* functions that come with cin.
* 
* The DeterminePlayerOne() function was particularly troubling,
* I had attempted to have it take in and work on a pointer to a
* Player object. The result of this was an extra Player object
* that caused errors within the game logic. To solve this I
* created instead a pointer to a player Object, left it
* unintialized and set it to the return value of
* DeterminePlayerOne(). The code was easier to understand and
* I also fixed the error that had been plaguing the program.
* 
* Pointers in general made the program more easy to work with,
* after the use of pointers with DeterminePlayerOne() I used it
* to clean up some line of code and transfered them into a
* function of their own. That cleaned up other calling functions.
* 
* Originally playersVector would have been playersArray, but the
* problem I faced was that playersArray needed to be initialized
* prior to the number of players being initialized and it could
* not be resized. The solution came in module 7 when I learned of
* vectors. Essentially a dynamically sized array, I did not have
* to wait for the player to determine the size of the array and
* the code would be less cluttered.
*/

#include <iostream>
#include <fstream>
#include "GameController.h"

using namespace std;

//Present the game options to the player
void GameController::PresentOptions()
{
	cout << "GAME MENU: " << endl << endl;
	cout << "1. New Game" << endl;
	cout << "2. View Rules" << endl;
	cout << "3. Quit" << endl << endl;
}

//Reads the game rules from a file and presents them to the user
void GameController::PresentRules()
{
	ifstream rulesFile;

	rulesFile.open("LDrules.txt");

	do
	{
		if (rulesFile.peek() == '*')
		{
			cout << endl << endl;
			system("pause");
			rulesFile.get();
		}
		else
		{
			cout << char(rulesFile.get());
		}
	} while (!rulesFile.eof());

	rulesFile.close();
}

//On the first round of the game, determines player one by the sum each player's stash
Player* GameController::DeterminePlayerOne()
{
	Player *player1;
	bool oneHighestSum = false;

	player1 = &playersVector[0];

	while (!oneHighestSum)
	{
		player1 = &playersVector[0];

		for (unsigned int i = 0; i < m_numPlayers; i++)
		{
			if (playersVector[i].GetDiceSum() > player1->GetDiceSum())
			{
				player1 = &playersVector[i];
			}
		}

		//Only one player may have the highest sum
		for (unsigned int i = 0; i < m_numPlayers; i++)
		{
			if (playersVector[i] != *player1)
			{

				if (playersVector[i].GetDiceSum() == player1->GetDiceSum())
				{
					RollAllDice();
					SumAllDice();
					oneHighestSum = false;
					break;
				}

				oneHighestSum = true;
			}
		}
	}

	return player1;
}

//Sets the number of players
void GameController::SetNumPlayers(unsigned int numPlayers)
{
	m_numPlayers = numPlayers;
}

//Sets the rotation direction of the players
void GameController::SetPlayRotation(string playRotation)
{
	m_playRotation = playRotation;
}

//Gets the game information/settings from the player
//ensures the validity of the entered information.
void GameController::GetGameInfo()
{
	int numPlayers;
	int playRotation;

	//Get a valid number of players (any whole number greater than 1)
	do
	{
		cout << "Liar's Dice requires 2 or more players." << endl;
		cout << "How many Players will be playing?: ";
		cin >> numPlayers;
		cout << endl;

		if (numPlayers >= 2)
		{
			SetNumPlayers(unsigned int (numPlayers));
		}
		else
		{
			cout << "Invalid entry." << endl;
			cout << "Please try again." << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while (numPlayers < 2);

	//Get the play rotation
	//If there are only two players, the rotation is negligible
	if (numPlayers == 2)
	{
		SetPlayRotation("cw");
	}
	else
	{
		do
		{
			cout << "Please choose Clockwise or Counterclockwise for the play rotation:" << endl;
			cout << "1. Clockwise\n2. Counterclockwise" << endl << endl;
			cin >> playRotation;
			cout << endl;

			switch (playRotation)
			{
			case 1:
				SetPlayRotation("cw");
				break;
			case 2:
				SetPlayRotation("ccw");
				break;
			default:
				cout << "I did not understand that command, please try again";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		} while (playRotation != 1 && playRotation != 2);
	}
}

//Retrieves the user input and returns it
int GameController::GetUserInput()
{
	unsigned int userInput;

	cin >> userInput;
	cout << endl;
	
	return userInput;
}

//Gets the current player's call and tests it for validity
void GameController::GetPlayerCall(Player* player1, int* pipsGuess, int* diceGuess, int *prevGuess)
{

	cout << "Player #" << player1->GetPlayerID() << ", please make your call..." << endl;

	do
	{
		cout << "Enter the the pip value you would like to guess...";
		cin >> *pipsGuess;

	} while (!CheckPipValue(*pipsGuess));

	do
	{
		cout << "Enter the amount of dice that have " << *pipsGuess << " pips facing up...";
		cin >> *diceGuess;
		cout << endl;

	} while (!CheckNumberOfDiceGuess(*diceGuess, *prevGuess));

	*prevGuess = *diceGuess;
}

//Validates the number of pips the user guessed
bool GameController::CheckPipValue(int pipValue)
{
	if (pipValue >= 1 && pipValue <= 6)
	{
		return true;
	}
	else
	{
		if (pipValue < 0)
		{
			cout << "Pip value cannot be negative, try again." << endl;
		}
		else if (pipValue > 6)
		{
			cout << "Pip value cannot be greater than 6, please try again." << endl;
		}
		else
		{
			cout << "Pip value cannot be 0, please try again." << endl;
		}

		return false;
	}
}

//Validates the number of pips the player guessed
bool GameController::CheckNumberOfDiceGuess(int numberOfDiceGuess, int previousDiceGuess)
{
	if (numberOfDiceGuess >= 0 && numberOfDiceGuess > previousDiceGuess)
	{
		return true;
	}
	else
	{
		if (numberOfDiceGuess < 0)
		{
			cout << "The number of dice guessed should be positive, please try again." << endl; 
		}
		else if (numberOfDiceGuess <= previousDiceGuess)
		{
			cout << "The number of dice guessed should be greater than the previous guess." << endl;
			cout << "Please try again." << endl;
		}

		return false;
	}
}

//Finds and returns the total number of dice with pip value that the player guessed
int GameController::FindTotalNumDiceOfPips(int pips)
{
	int totalNumDiceOfPips = 0;
	for (int i = 0; i < m_numPlayers; i++)
	{
		totalNumDiceOfPips += playersVector[i].FindNumDiceOfPips(pips);
	}

	return totalNumDiceOfPips;
}

//Create the player profiles, assigning each their own ID.
void GameController::CreatePlayers()
{
	for (unsigned int i = 0; i < m_numPlayers; i++)
	{
		playersVector.push_back(Player());
	}
}

//Roll all the players' dice
void GameController::RollAllDice()
{
	cout << "Rolling all player dice" << endl;
	system("pause");
	cout << endl;

	for (unsigned int i = 0; i < m_numPlayers; i++)
	{
		playersVector[i].RollDice();
	}
}

//Sums all the players' dice
void GameController::SumAllDice()
{
	for (unsigned int i = 0; i < m_numPlayers; i++)
	{
		playersVector[i].SumDice();
	}
}

//Displays all the players' dice
void GameController::ShowAllDice()
{
	for (unsigned int i = 0; i < m_numPlayers; i++)
	{
		playersVector[i].DisplayDice();
	}
}

//Defines the main game loop
void GameController::PlayGame()
{
	static Player* player1;
	int currentPlayer;
	int pipValueGuess, numberOfDiceGuess;
	int playerInput, previousDiceGuess = -1;
	string isOrAre;

	//Roll dice to determine player 1 on the first round
	if (m_roundNumber == 1)
	{
		RollAllDice();
		SumAllDice();
		player1 = DeterminePlayerOne();
	}

	//Clear the screen to prevent player's from viewing other players' stash
	system("CLS");

	cout << "Player #" << player1->GetPlayerID() << ", you will begin round " << m_roundNumber++ << "." << endl << endl;

	RollAllDice();

	//Since the program plays in a console window, warn players when their dice is
	//about to be displayed in an effort to enforce fair gameplay.
	cout << "Displaying player dice . . ." << endl;
	system("pause");
	cout << endl;
	player1->DisplayDice();

	GetPlayerCall(player1, &pipValueGuess, &numberOfDiceGuess, &previousDiceGuess);

	currentPlayer = player1->GetPlayerID();

	//Allow each player the chance to accept or call player1's guess.
	for (int i = 0; i < m_numPlayers; i++)
	{
		//Move to the next player 
		if (m_playRotation == "cw")
		{

			++currentPlayer;

			if (currentPlayer > m_numPlayers)
			{
				currentPlayer = 1;
			}
		}
		else if (m_playRotation == "ccw")
		{
			--currentPlayer;

			if (currentPlayer <= 0)
			{
				currentPlayer = m_numPlayers;
			}
		}


		system("CLS");

		//Display the previous player's guess to the next player
		cout << "Player #" << player1->GetPlayerID() << " has guessed " << previousDiceGuess << " " << pipValueGuess << "'s." << endl << endl;
 		cout << "Player #" << playersVector[currentPlayer - 1].GetPlayerID() << "'s turn." << endl;
		cout << "Displaying player dice . . ." << endl;

		system("pause");
		cout << endl;

		playersVector[currentPlayer - 1].DisplayDice();

		//Get the next player's call
		cout << "Player #" << playersVector[currentPlayer - 1].GetPlayerID();
		cout << ", do you accept Player #" << player1->GetPlayerID() << "'s call?" << endl;
		cout << "1. Accept" << endl;
		cout << "2. Liar" << endl << endl;

		do
		{

			playerInput = GetUserInput();

			if (playerInput < 1 || playerInput > 2)
			{
				cout << "I do not recognize that input, try again..." << endl;
				cout << "1. Accept" << endl;
				cout << "2. Call Liar" << endl << endl;
			}

		} while (playerInput < 1 || playerInput > 2);

		if (playerInput == 1)
		{

			player1 = &playersVector[currentPlayer - 1];

			//Ensures that each player only has the chance to make a call once in each round.
			if (i < m_numPlayers - 1)
			{
				GetPlayerCall(player1, &pipValueGuess, &numberOfDiceGuess, &previousDiceGuess);
			}
		}

		//Determine the winner and ends the current round if a player selects the liar option
		else if (playerInput == 2)
		{
			int actualNumDice = FindTotalNumDiceOfPips(pipValueGuess);

			ShowAllDice();
			
			cout << "There ";
			(actualNumDice != 1) ? (cout << "are ") : (cout << "is ");
			cout << actualNumDice << " " << pipValueGuess << "'s in the pool." << endl << endl;

			if (actualNumDice == numberOfDiceGuess)
			{
				cout << "Congratulations! Player #" << player1->GetPlayerID() << ", you won this round!" << endl;
				cout << "Player #" << playersVector[currentPlayer - 1].GetPlayerID() << ", you must pay the forfeit!" << endl << endl;
				break;
			}
			else
			{
				cout << "Congratulations! Player #" << playersVector[currentPlayer - 1].GetPlayerID() << ", you won this round!" << endl;
				cout << "Player #" << player1->GetPlayerID() << ", you must pay the forfeit!" << endl << endl;
				player1 = &playersVector[currentPlayer - 1];
				break;
			}
		}
	}
}

//Returns true or false depending on whether the user would like to play again
bool GameController::Continue()
{
	int userInput;

	cout << "Would you like to continue to round " << m_roundNumber << "?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	do
	{

		userInput = GetUserInput();

		if (userInput < 1 || userInput > 2)
		{
			cout << "I do not recognize that input, try again..." << endl;
			cout << "1. Yes, we would like to continue." << endl;
			cout << "2. No, we would like to quit." << endl << endl;
		}

	} while (userInput < 1 || userInput > 2);
	
	if (userInput == 1)
	{
		return true;
	}
	else if (userInput == 2)
	{
		return false;
	}
}

//Retrieves user and player information then begins to play the game.
void GameController::Start()
{
	cout << "Welcome to LIAR'S DICE!" << endl << endl;

	bool quit = false;
	unsigned int previousWinner;
	

	//Validate user input and determine the appropriate action
	while (!quit)
	{
		PresentOptions();
		switch (GetUserInput())
		{
			case 1:
				m_roundNumber = 1;

				GetGameInfo();
				CreatePlayers();
				
				do
				{
					PlayGame();
				} while (Continue());

				break;
			case 2:
				PresentRules();
				break;
			case 3:
				quit = true;
				break;
			default:
				cout << "I do not recognize that command, try again." << endl << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
		}
	}
}