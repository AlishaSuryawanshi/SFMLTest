#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<iostream>



int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 800), "My window");
	window->setFramerateLimit(20);
	sf::Texture BackTexture;
	BackTexture.loadFromFile("Background.png");
	sf::Sprite Background(BackTexture);
	Background.setScale(2, 2);

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

			window->clear();
			window->draw(Background);
			(*window).display();
		}
	}

	return 0;
}