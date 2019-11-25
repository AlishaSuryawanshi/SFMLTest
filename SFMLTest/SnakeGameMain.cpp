#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<string.h>
#include "PlayerController.h"

enum Textures
{
	Red, Green, Head, Body, Background,Score
};

int x, y,Scores;
sf::Font font;
sf::RenderWindow* window;
sf::Texture TexturesArray[10];
sf::Sprite BackgroundSprite;
sf::Sprite SnakeHeadSprite, BodySprite;
sf::Sprite FoodRedSprite, FoodGreenSprite;
sf::Sprite ScoreSprite;
PlayerController PC;
sf::Text ScoreText;




void LoadTextures()
{
	TexturesArray[Background].loadFromFile("Background.png");
	TexturesArray[Head].loadFromFile("SnakeHead.png");
	TexturesArray[Body].loadFromFile("BodyTexture.png");
	TexturesArray[Score].loadFromFile("Score.png");
	for (int i = Red; i <= Green; i++)
	{
		TexturesArray[i].loadFromFile("Food" + std::to_string(i) + ".png");
	}
	
	BackgroundSprite.setTexture(TexturesArray[Background]);
	SnakeHeadSprite.setTexture(TexturesArray[Head]);
	BodySprite.setTexture(TexturesArray[Body]);
	FoodRedSprite.setTexture(TexturesArray[Red]);
	FoodGreenSprite.setTexture(TexturesArray[Green]);
	ScoreSprite.setTexture(TexturesArray[Score]);
}

void SetScales()
{
	BackgroundSprite.setScale(2, 2);
	SnakeHeadSprite.setScale(.2, .2);
	BodySprite.setScale(.2, .2);
	FoodRedSprite.setScale(.4,.4);
	FoodGreenSprite.setScale(.2,.2);
	ScoreSprite.setScale(.5,.5);
	ScoreText.setScale(.5,.5);
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
	x = 5;
	y = 0;
	LoadTextures();
	SetScales();
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "My window");
	window->setFramerateLimit(20);
	GenerateFood(); //Temp
	FoodRedSprite.setPosition(-100, -100);
	BodySprite.setPosition(-100, -100);
	SnakeHeadSprite.setOrigin(5,5);
	std::cout<<SnakeHeadSprite.getOrigin().x<<" "<<SnakeHeadSprite.getOrigin().y;
	ScoreSprite.setPosition(560,640);
	ScoreText.setPosition(600, 650);
	ScoreText.setString("Score" + std::to_string(Scores));
	ScoreSprite.setColor(sf::Color(0, 0, 0));
	font.loadFromFile("Alata-Regular.ttf");
	ScoreText.setFillColor(sf::Color(255, 255, 255));
	ScoreText.setFont(font);
}


void MoveHead()
{
	PC.UpdatePositions(SnakeHeadSprite.getPosition());
	SnakeHeadSprite.move(x, y);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x != 5 && y != 0)
			{
				x = -5;
				y = 0;
				SnakeHeadSprite.setRotation(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x != -5 && y != 0)
			{
				x = 5;
				y = 0;
				SnakeHeadSprite.setRotation(180);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && x != 0 && y != 5)
			{
				x = 0;
				y = -5;
				SnakeHeadSprite.setRotation(90);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && x != 0 && y != -5)
			{
				x = 0;
				y = 5;
				SnakeHeadSprite.setRotation(270);
			}

			if (FoodGreenSprite.getGlobalBounds().left < SnakeHeadSprite.getGlobalBounds().left &&
				FoodRedSprite.getGlobalBounds().top < SnakeHeadSprite.getGlobalBounds().top &&
				FoodRedSprite.getGlobalBounds().height > SnakeHeadSprite.getGlobalBounds().height &&
				FoodRedSprite.getGlobalBounds().width > SnakeHeadSprite.getGlobalBounds().width)
			{
				GenerateFood();
				
				
				PC.AddFood(&TexturesArray[Body]);
			}

			MoveHead();
			window->clear();
			window->draw(BackgroundSprite);
			window->draw(ScoreSprite);
			window->draw(ScoreText);
			window->draw(FoodRedSprite);
			window->draw(FoodGreenSprite);
			window->draw(SnakeHeadSprite);

			//for (sf::Sprite& Sprite : PC.BodySprites)

			if(PC.BodySprites.size() >= 1)
			{
				for(int i=0;i<PC.BodySprites.size();i++)
					window->draw(PC.BodySprites[i]);
			}
			window->display();
		}
	}

	return 0;
}