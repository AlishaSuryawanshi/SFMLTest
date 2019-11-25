#include "PlayerController.h"

PlayerController::PlayerController()
{
	Lives = 3;
}

int PlayerController::GetLives()
{
	return Lives;
}

void PlayerController::GetDamage()
{
	Lives--;
}

void PlayerController::AddFood(sf::Texture* tex)
{
	sf::Sprite Temp(*tex);
	Temp.setScale(.2, .2);
	if (BodySprites.size() > 1)
	{
		Temp.setPosition(BodySprites[0].getPosition());
	}
	else
	{
		Temp.setPosition(5,5);
	}
		BodySprites.push_back(Temp);
}

void PlayerController::UpdatePositions(sf::Vector2f HeadPosition)
{
	//Code for Body

	if(BodySprites.size()>=1)
		for (int i=0;i<BodySprites.size()-1; i++)
		{
			BodySprites[i + 1].setPosition(BodySprites[i].getPosition());  //Next Position Value Gets Previous
			
		}
	if(BodySprites.size() > 0)
		BodySprites[0].setPosition(HeadPosition);
}
