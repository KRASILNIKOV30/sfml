#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <corecrt_math_defines.h>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
	constexpr int POINT_COUNT = 200;
	constexpr int SPEED = 100;
	constexpr int radius = 200;
	const sf::Vector2f roseRadius = { 200.f, 80.f };
	const sf::Vector2f position = { 400.f, 300.f };
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Rose", sf::Style::Default, settings);
	sf::Clock iterClock;
	sf::Clock analitycalClock;

	window.setVerticalSyncEnabled(true);

	sf::ConvexShape rose;
	rose.setFillColor(sf::Color::Red);
	rose.setPosition(300, 400);

	rose.setPointCount(POINT_COUNT);
	for (int i = 0; i < POINT_COUNT; i++)
	{
		float angle = static_cast<float>(2 * M_PI * i) / static_cast<float>(POINT_COUNT);
		sf::Vector2f point = {
			200 * std::sin(6 * angle) * std::sin(angle),
			200 * std::sin(6 * angle) * std::cos(angle)
		};
		rose.setPoint(i, point);
	}

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		const float t = clock.restart().asSeconds();
		rose.setRotation(rose.getRotation() + t * SPEED);
		const float radians = 2 * M_PI / 360 * rose.getRotation();
		rose.setPosition(position + sf::Vector2f{ radius * std::cos(radians), radius * std::sin(radians) });

		window.clear(sf::Color::Black);
		window.draw(rose);
		window.display();
	}
	return 0;
}