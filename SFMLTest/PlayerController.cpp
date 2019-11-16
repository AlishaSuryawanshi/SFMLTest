#include "PlayerController.h"

PlayerController::PlayerController()
{
	Lives = 3;
	Positions.push_back(sf::Vector2f(0, 0));
	Positions.push_back(sf::Vector2f(0, 0));
}

int PlayerController::GetLives()
{
	return Lives;
}

void PlayerController::GetDamage()
{
	Lives--;
}

void PlayerController::UpdatePositions(sf::Vector2f HeadPosition)
{
	//Code for Body

	for (int i=0;i<Positions.size()-1; i++)
	{
		Positions[i + 1] = Positions[i];  //Next Position Value Gets Previous
	}

	Positions[0] = HeadPosition;
}
