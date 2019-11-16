#pragma once
#include<vector>
#include<SFML/System.hpp>

class PlayerController
{
	int Lives;

public:
	PlayerController();
	
	std::vector<sf::Vector2f> Positions;
	int GetLives();
	void GetDamage();

	void UpdatePositions(sf::Vector2f HeadPosition);

};

