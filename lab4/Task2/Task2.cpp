#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <corecrt_math_defines.h>
#include <valarray>
#include <SFML/Window/Event.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr int POINT_COUNT = 100;

struct Eyes
{
	sf::ConvexShape leftWhite;
	sf::ConvexShape rightWhite;
	sf::ConvexShape left;
	sf::ConvexShape right;
	sf::Vector2f radius = { 20, 40 };
	sf::Vector2f radiusWhite = { 80, 160 };
	sf::Vector2f leftPosition = { 340, 340 };
	sf::Vector2f rightPosition = { 540, 340 };
};

float toDegrees(const float radians)
{
	return static_cast<float>(static_cast<double>(radians) * 180 / M_PI);
}

void Init(Eyes& eyes)
{
	eyes.leftWhite.setPosition(300, 300);
	eyes.rightWhite.setPosition(500, 300);
	eyes.left.setPosition(eyes.leftPosition);
	eyes.right.setPosition(eyes.rightPosition);
	eyes.left.setOrigin(40, 40);
	eyes.right.setOrigin(40, 40);

	eyes.leftWhite.setFillColor(sf::Color::White);
	eyes.rightWhite.setFillColor(sf::Color::White);
	eyes.left.setFillColor(sf::Color::Black);
	eyes.right.setFillColor(sf::Color::Black);

	eyes.leftWhite.setPointCount(POINT_COUNT);
	eyes.rightWhite.setPointCount(POINT_COUNT);
	eyes.left.setPointCount(POINT_COUNT);
	eyes.right.setPointCount(POINT_COUNT);

	for (int i = 0; i < POINT_COUNT; ++i)
	{
		const float angle = static_cast<float>(2 * M_PI * i) / static_cast<float>(POINT_COUNT);
		sf::Vector2f pointWhite = {
			eyes.radiusWhite.x * std::sin(angle),
			eyes.radiusWhite.y * std::cos(angle)
		};
		sf::Vector2f point = {
			eyes.radius.x * std::sin(angle),
			eyes.radius.y * std::cos(angle)
		};
		eyes.leftWhite.setPoint(i, pointWhite);
		eyes.rightWhite.setPoint(i, pointWhite);
		eyes.left.setPoint(i, point);
		eyes.right.setPoint(i, point);
	}
}

void DrawFrame(sf::RenderWindow& window, Eyes const& eyes)
{
	window.clear(sf::Color::Black);
	window.draw(eyes.leftWhite);
	window.draw(eyes.rightWhite);
	window.draw(eyes.left);
	window.draw(eyes.right);
	window.display();
}

void OnMouseMove(sf::Event::MouseMoveEvent const& event, sf::Vector2f& mousePosition)
{
	mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
}

sf::Vector2f ToEuclidian(const sf::Vector2f radius, const float angle)
{
	return
	{
		radius.x * std::cos(angle),
		radius.y * std::sin(angle),
	};
}

void Update(sf::Vector2f const& mousePosition, sf::ConvexShape& eye, const sf::Vector2f position)
{
	const sf::Vector2f delta = mousePosition - eye.getPosition();
	const float angle = std::atan2(delta.y, delta.x);

	eye.setPosition(position + ToEuclidian({20, 40 }, angle));
}

void PollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			OnMouseMove(event.mouseMove, mousePosition);
			break;
		default: break;
		}
	}
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pointer", sf::Style::Default, settings);
	sf::Clock clock;

	sf::Vector2f mousePosition;

	window.setVerticalSyncEnabled(true);

	Eyes eyes;
	Init(eyes);

	while (window.isOpen())
	{
		double t = clock.restart().asSeconds();
		PollEvents(window, mousePosition);
		Update(mousePosition, eyes.left, eyes.leftPosition);
		Update(mousePosition, eyes.right, eyes.rightPosition);
		DrawFrame(window, eyes);
	}
	return 0;
}