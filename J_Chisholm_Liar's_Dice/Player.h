//This header file contains the declarations and functions of data
//used in the Player.cpp class

#pragma once

class Player
{

private:

	static unsigned int m_classID;
	unsigned int m_playerID;
	unsigned int m_stash[5];
	unsigned int m_diceSum;

public:

	Player();

	unsigned int GetDiceSum();
	unsigned int GetPlayerID();

	void RollDice();
	void SumDice();
	void DisplayDice();
	void ResetDiceSum();
	int FindNumDiceOfPips(int);

	bool operator!=(const Player&);
	bool operator==(const Player&);
};