/*
The Player class holds all relevant information for each player
such as the name, player number, their dice and provides the ability
to roll the dice.
*/

/*
* MAJOR PROBLEMS:
* 
* The main problem I had with the player class was being unable to
* maintain the player ID's until I found a way through a static
* variable which retains its value through function calls or the
* instantiation of an object. I could update another variable based
* on the incrementing of said static variable to produce self
* creating player ID's.
* 
* Another issue I faced was finding a solution to the length of an
* array. C++ does not have such a function written in for arrays
* however I was able to find a solution in the way of dividing the
* size of the array by the size of the variables it holds. This
* allowed me to properly iterate over the variables in the array.
*/

#include <iostream>
#include "Player.h"

using namespace std;

//Default constructor
Player::Player()
{
	m_playerID = ++m_classID;
	for (int i = 0; i < 5; i++)
	{
		m_stash[i] = 0;
	}
	m_diceSum = 0;
}

//Returns the player ID number
unsigned int Player::GetPlayerID()
{
	return m_playerID;
}

//Get the current total sum of the upward facing pips on player's dice
unsigned int Player::GetDiceSum()
{
	return m_diceSum;
}

//Rolls the player's dice
void Player::RollDice()
{
	ResetDiceSum();

	for (int i = 0; i < sizeof(m_stash)/sizeof(m_stash[0]); i++)
	{
		m_stash[i] = (rand() % 6) + 1;
	}
}

//Sums up the upward facing pips on the player's thrown dice
void Player::SumDice()
{
	for (int i = 0; i < sizeof(m_stash)/sizeof(m_stash[0]); i++)
	{
		m_diceSum += m_stash[i];
	}

}

//Shows the player their dice
void Player::DisplayDice()
{
	cout << "Player #" << m_playerID << "'s stash: ";
	for (int i = 0; i < sizeof(m_stash)/sizeof(m_stash[0]); i++)
	{
		cout << m_stash[i] << " ";
	}
	cout << endl << endl;
}

//Resets the sum of player's dice
void Player::ResetDiceSum()
{
	m_diceSum = 0;
}

//Function created to aid in finding the winner of the round.
//Finds the number of dice within the player's stash that has
//a certain number of pips facing up
int Player::FindNumDiceOfPips(int pips)
{
	int numDiceOfPips = 0;
	for (int i = 0; i < sizeof(m_stash) / sizeof(m_stash[0]); i++)
	{
		if (m_stash[i] == pips)
		{
			++numDiceOfPips;
		}
	}
	
	return numDiceOfPips;
}

//Overload operator !=
bool Player::operator!=(const Player& otherPlayer)
{
	if (this->m_playerID != otherPlayer.m_playerID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Overload operator == 
bool Player::operator==(const Player& otherPlayer)
{
	if (this->m_playerID == otherPlayer.m_playerID)
	{
		return true;
	}
	else
	{
		return false;
	}
}