#pragma once
#include<SFML/Graphics.hpp>

enum Color {Red, Yellow, White};


class Food
{
	int Power;
	Color color;
	sf::Vector2f Position;
};

