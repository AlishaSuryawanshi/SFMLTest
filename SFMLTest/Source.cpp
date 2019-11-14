#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<iostream>


// Ball cannot go out of screen change to opposite direction

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "My window");
	int X,Y;

	int RateX , RateY ;
	
	RateX = rand() % 10;
	RateY = rand() % 10;

	sf::Texture BallTexture;
	sf::Sprite BallSprite;

	bool isLoaded = BallTexture.loadFromFile("Ball.png");

	BallSprite.setTexture(BallTexture);
	BallSprite.setScale(.10f, .10f);

	//Frame Limited to 10 per sec
	window->setFramerateLimit(20);

	if (isLoaded)
		std::cout << "Load Successfull";

	std::cout << "Height = " << BallSprite.getGlobalBounds().height << "Width = " << BallSprite.getGlobalBounds().width;

	// run the program as long as the window is open
	while (window->isOpen())
	{
		
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event; 

		window->pollEvent(event);
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::Resized)
			{
				sf::Vector2u NewSize = window->getSize();
				delete window;
				window = new sf::RenderWindow(sf::VideoMode(NewSize.x, NewSize.y), "NewWindow");
			}
		
			if (BallSprite.getPosition().y > window->getSize().y - 72)
				Y = -1;
			if (BallSprite.getPosition().y <= 1)
				Y = 1;
			if (BallSprite.getPosition().x > window->getSize().x - 72)
				X = -1;
			if (BallSprite.getPosition().x <= 1)
				X = 1;
			


			BallSprite.setPosition(BallSprite.getPosition().x + (X * RateX), BallSprite.getPosition().y + (Y * RateY));
			
			window->clear();
			window->draw(BallSprite);
			(*window).display();
		}
	}
	
	return 0;
}