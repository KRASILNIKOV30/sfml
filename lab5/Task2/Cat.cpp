#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <corecrt_math_defines.h>
#include <valarray>
#include <SFML/Window/Event.hpp>
#include "Entity.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr int SPEED = 100;

void DrawFrame(sf::RenderWindow& window, Entity const& cat, Entity const& laser)
{
	window.clear(sf::Color::White);
	laser.Draw(window);
	cat.Draw(window);
	window.display();
}

void OnMouseClick(sf::Event::MouseButtonEvent const& event, Entity& laser)
{
	laser.GetImage().setPosition(static_cast<float>(event.x), static_cast<float>(event.y));
}

void Update(sf::Vector2f const& mousePosition, Entity& cat, const float t)
{
	const sf::Vector2f delta = mousePosition - cat.GetImage().getPosition();
	const float deltaLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	if (deltaLength < 3)
	{
		return;
	}
	const sf::Vector2f direction = sf::Vector2f(delta.x / deltaLength, delta.y / deltaLength);
	cat.GetImage().move(direction.x * SPEED * t, direction.y * SPEED * t);
	if (delta.x < 0 && !cat.IsFlipped() || delta.x > 0 && cat.IsFlipped())
	{
		cat.Flip();
	}
}

void PollEvents(sf::RenderWindow& window, Entity& laser)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			OnMouseClick(event.mouseButton, laser);
			break;
		default: break;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pointer", sf::Style::Default);
	sf::Clock clock;

	sf::Vector2f mousePosition;

	window.setVerticalSyncEnabled(true);

	sf::ConvexShape pointer;
	Entity cat("cat.png");
	Entity laser("laser.png");
	cat.GetImage().setOrigin(cat.GetSize().x / 2, cat.GetSize().y / 2);
	laser.GetImage().setOrigin(laser.GetSize().x / 2, laser.GetSize().y / 2);
	cat.GetImage().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	laser.GetImage().setPosition(50, 50);

	while (window.isOpen())
	{
		float t = clock.restart().asSeconds();
		PollEvents(window, laser);
		Update(laser.GetImage().getPosition(), cat, t);
		DrawFrame(window, cat, laser);
	}
	return 0;
}