#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <corecrt_math_defines.h>
#include <valarray>
#include <SFML/Window/Event.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr int ROTATION_SPEED = 90;
constexpr int SPEED = 20;

float toDegrees(const float radians)
{
	return static_cast<float>(static_cast<double>(radians) * 180 / M_PI);
}

void Init(sf::ConvexShape& pointer)
{
	pointer.setPointCount(3);
	pointer.setPoint(0, { 40, 0 });
	pointer.setPoint(1, { -20, -20 });
	pointer.setPoint(2, { -20, 20 });
	pointer.setPosition(400, 300);
	pointer.setFillColor(sf::Color::Red);
}

void DrawFrame(sf::RenderWindow& window, sf::ConvexShape const& pointer)
{
	window.clear(sf::Color::Black);
	window.draw(pointer);
	window.display();
}

void OnMouseMove(sf::Event::MouseMoveEvent const& event, sf::Vector2f& mousePosition)
{
	mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
}

void Update(sf::Vector2f const& mousePosition, sf::ConvexShape& pointer, const double t)
{
	const sf::Vector2f delta = mousePosition - pointer.getPosition();
	const float angle = std::atan2(delta.y, delta.x);
	double mouseDegrees = toDegrees(angle);
	mouseDegrees = mouseDegrees > 0 ? mouseDegrees : 360 + mouseDegrees;
	const double arrowDegrees = pointer.getRotation();
	double degreesDelta = mouseDegrees - arrowDegrees;
	degreesDelta = std::abs(degreesDelta) > 180
		? degreesDelta > 0
			? -(std::min(mouseDegrees, arrowDegrees) + 360 - std::max(mouseDegrees, arrowDegrees))
			: (std::min(mouseDegrees, arrowDegrees) + 360 - std::max(mouseDegrees, arrowDegrees))
		: degreesDelta;
	const double speed = degreesDelta / t;
	degreesDelta = speed > 0 ? std::min(ROTATION_SPEED * t, degreesDelta) : std::max(-ROTATION_SPEED * t, degreesDelta);
	pointer.rotate(static_cast<float>(degreesDelta));
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
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pointer", sf::Style::Default);
	sf::Clock clock;

	sf::Vector2f mousePosition;

	window.setVerticalSyncEnabled(true);

	sf::ConvexShape pointer;
	Init(pointer);

	while (window.isOpen())
	{
		double t = clock.restart().asSeconds();
		PollEvents(window, mousePosition);
		Update(mousePosition, pointer, t);
		DrawFrame(window, pointer);
	}
	return 0;
}