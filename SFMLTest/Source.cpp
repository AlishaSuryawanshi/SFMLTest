#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<iostream>



// Ball cannot go out of screen change to opposite direction





int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	
	sf::Texture BallTexture;
	sf::Sprite BallSprite;

	

	bool isLoaded = BallTexture.loadFromFile("Ball.png");

	BallSprite.setTexture(BallTexture);
	BallSprite.setScale(.10f, .10f);

	//Frame Limited to 10 per sec
	window.setFramerateLimit(10);

	if (isLoaded)
		std::cout << "Load Successfull";


	// run the program as long as the window is open
	while (window.isOpen())
	{
		
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event; 

		window.pollEvent(event);
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			BallSprite.setPosition(BallSprite.getPosition().x + 1, BallSprite.getPosition().y + 1);
			
			window.clear();
			window.draw(BallSprite);
			window.display();
		}
	}
	
	return 0;
}