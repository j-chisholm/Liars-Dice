/*
Liar's Dice
Jevon Chisholm
IT 312
Final Project

This program plays the Liar's Dice game using the original rules
of the game. The game is played on the console window with a
minimum of two players and has no upper limit.
*/

#include <iostream>
#include <ctime>
#include "Player.h"
#include "GameController.h"

unsigned int Player::m_classID = 0;

int main()
{
	srand(time(NULL));

	GameController gameController;

	gameController.Start();

	return 0;
	
}