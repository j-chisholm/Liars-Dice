//This header file contains the declarations and functions of data
//used in the GameController.cpp class

#pragma once

#include "Player.h"
#include <vector>

using std::vector;
using PlayersVector = vector<Player>;

class GameController
{
private:

	PlayersVector playersVector;

	unsigned int m_numPlayers, m_roundNumber = 1;
	std::string m_playRotation;

	void SetNumPlayers(unsigned int);
	void SetPlayRotation(std::string);
	void GetGameInfo();
	int GetUserInput();
	void GetPlayerCall(Player*, int*, int*, int*);
	bool CheckPipValue(int);
	bool CheckNumberOfDiceGuess(int, int);
	int FindTotalNumDiceOfPips(int);

	void CreatePlayers();
	void RollAllDice();
	void SumAllDice();
	void ShowAllDice();

	void PlayGame();
	bool Continue();

	void PresentOptions();
	void PresentRules();
	Player* DeterminePlayerOne();

public:

	void Start();

};