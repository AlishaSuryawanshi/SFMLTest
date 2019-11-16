#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<string.h>
#include "PlayerController.h"

enum Textures
{
	Red, Green, Head, Body, Background
};

int x, y;
sf::RenderWindow* window;
sf::Texture TexturesArray[10];
sf::Sprite BackgroundSprite;
sf::Sprite SnakeHeadSprite, BodySprite;
sf::Sprite FoodRedSprite, FoodGreenSprite;
PlayerController PC;


void LoadTextures()
{
	TexturesArray[Background].loadFromFile("Background.png");
	TexturesArray[Head].loadFromFile("SnakeHead.png");
	TexturesArray[Body].loadFromFile("BodyTexture.png");
	
	for (int i = Red; i <= Green; i++)
	{
		TexturesArray[i].loadFromFile("Food" + std::to_string(i) + ".png");
	}

	BackgroundSprite.setTexture(TexturesArray[Background]);
	SnakeHeadSprite.setTexture(TexturesArray[Head]);
	BodySprite.setTexture(TexturesArray[Body]);
	FoodRedSprite.setTexture(TexturesArray[Red]);
	FoodGreenSprite.setTexture(TexturesArray[Green]);
}

void SetScales()
{
	BackgroundSprite.setScale(2, 2);
	SnakeHeadSprite.setScale(.2, .2);
	BodySprite.setScale(.2, .2);
	FoodRedSprite.setScale(.4,.4);
	FoodGreenSprite.setScale(.2,.2);

}

//Food Functions
void GenerateFood()
{
	FoodGreenSprite.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
}
void GenerateBonusFood()
{
	FoodRedSprite.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
}

void Initialise()
{
	x = 1;
	y = 0;
	LoadTextures();
	SetScales();
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "My window");
	window->setFramerateLimit(20);
	GenerateFood(); //Temp
	FoodRedSprite.setPosition(-100, -100);
	BodySprite.setPosition(-100, -100);
	SnakeHeadSprite.setOrigin(SnakeHeadSprite.getGlobalBounds().width / 2.0, SnakeHeadSprite.getGlobalBounds().height / 2.0);
}


void MoveHead()
{
	sf::Vector2f Current = SnakeHeadSprite.getPosition();
	PC.UpdatePositions(Current);
	SnakeHeadSprite.setPosition(Current.x + x, Current.y + y);
}




int main()
{
	
	Initialise();
	while (window->isOpen())
	{
		sf::Event event;

		window->pollEvent(event);
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::Resized)
			{
				sf::Vector2u NewSize = window->getSize();
				delete window;
				window = new sf::RenderWindow(sf::VideoMode(NewSize.x, NewSize.y), "NewWindow");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x!=1 && y!=0)
			{
				x = -1;
				y = 0;
				SnakeHeadSprite.setRotation(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x != -1 && y != 0)
			{
				x = 1;
				y = 0;
				SnakeHeadSprite.setRotation(180);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && x != 0 && y != 1)
			{
				x = 0;
				y = -1;
				SnakeHeadSprite.setRotation(90);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && x != 0 && y != -1)
			{
				x = 0;
				y = 1;
				SnakeHeadSprite.setRotation(270);
			}

			if (FoodGreenSprite.getGlobalBounds().left < SnakeHeadSprite.getGlobalBounds().left &&
				FoodRedSprite.getGlobalBounds().top < SnakeHeadSprite.getGlobalBounds().top &&
				FoodRedSprite.getGlobalBounds().height > SnakeHeadSprite.getGlobalBounds().height &&
				FoodRedSprite.getGlobalBounds().width > SnakeHeadSprite.getGlobalBounds().width)
			{
				GenerateFood();
				sf::Vector2f NewPosition;
				//double Direction = (((PC.Positions[PC.Positions.size() - 1]).y - (PC.Positions[PC.Positions.size() - 2]).y)) / (((PC.Positions[PC.Positions.size() - 1]).x - (PC.Positions[PC.Positions.size() - 2]).x));
				NewPosition.y = 17 * (((PC.Positions[PC.Positions.size() - 1]).y - (PC.Positions[PC.Positions.size() - 2]).y));
				NewPosition.x = 17 * (((PC.Positions[PC.Positions.size() - 1]).x - (PC.Positions[PC.Positions.size() - 2]).x));

				PC.Positions.push_back(NewPosition);
			}

			MoveHead();
			window->clear();
			window->draw(BackgroundSprite);
			window->draw(FoodRedSprite);
			window->draw(FoodGreenSprite);
			window->draw(SnakeHeadSprite);

			for (sf::Vector2f Position : PC.Positions)
			{
				BodySprite.setPosition(Position);
				window->draw(BodySprite);
			}
			(*window).display();
		}
	}

	return 0;
}