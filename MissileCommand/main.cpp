#include "Game.h"
#include "Message.h"
#include "Messenger.h"
#include "SFML/System/Sleep.hpp"
#include "MissileCommandGame.h"

int main()
{
	// Create window instance
	sf::RenderWindow WindowInstance(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "MissileCommand", sf::Style::None);
	WindowInstance.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));
	WindowInstance.setPosition(sf::Vector2i(0, 0));

	sf::View TestView = WindowInstance.getView();
	TestView.setCenter(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
	WindowInstance.setView(TestView);

	WindowInstance.setFramerateLimit(60);

	// Set the window inactive so another thread can pick it up.
	WindowInstance.setActive(false);

	// Create an instance of the game here.
	std::unique_ptr<MissileCommandGame> GameInstance = std::make_unique<MissileCommandGame>(&WindowInstance);

	// Create an event holder here for our event polling.
	sf::Event WindowEvent;

	while (GameInstance->IsActive())
	{
		while (WindowInstance.pollEvent(WindowEvent))
		{
			switch (WindowEvent.type)
			{
				case sf::Event::Closed:
					GameInstance->EndGame();
					break;
				case sf::Event::KeyPressed:
					GameInstance->QueueMessage("KeyEvents", std::make_shared<Message>(MESSAGE_TYPE_INPUT, (double)WindowEvent.key.code, true));
					break;
				case sf::Event::Resized:
					WindowInstance.setSize(sf::Vector2u(WindowEvent.size.width, WindowEvent.size.height));
					break;
				case sf::Event::MouseButtonPressed:
					if (WindowEvent.mouseButton.button == sf::Mouse::Left)
					{
						GameInstance->QueueMessage("MouseEvents",
								std::make_unique<Message>(MESSAGE_TYPE_MOUSE,
								std::pair<double, double>(WindowEvent.mouseButton.x, WindowEvent.mouseButton.y),
								std::string("LeftPressed")));
					}
					break;
			}
		}

		sf::sleep(sf::milliseconds(100));
	}

	return 0;
}