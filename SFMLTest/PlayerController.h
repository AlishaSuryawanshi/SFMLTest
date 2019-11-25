#pragma once
#include<vector>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<queue>

class PlayerController
{
	int Lives;

public:
	PlayerController();
	
	std::vector<sf::Sprite> BodySprites;
	int GetLives();
	void GetDamage();
	void AddFood(sf::Texture*);
	void UpdatePositions(sf::Vector2f);

};

