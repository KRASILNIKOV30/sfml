#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wave Moving Ball", sf::Style::Default);
    sf::Clock iterClock;
    sf::Clock analitycalClock;

    window.setVerticalSyncEnabled(true);

    sf::Vector2f position = { 10, 350 };

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color::Red);

    float speedX = 300;
    constexpr float amplitudeY = 80;
    constexpr float period = 2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (position.x > WINDOW_WIDTH - 2 * BALL_SIZE || position.x < 0)
        {
            speedX *= -1;
        }

        const float iterTime = iterClock.restart().asSeconds();
        const float analitycalTime = analitycalClock.getElapsedTime().asSeconds();
        const float wavePhase = analitycalTime * float(2 * M_PI);
        const float x = speedX * iterTime;
        const float y = amplitudeY * std::sin(wavePhase / period);
        position.x += x;
        ball.setPosition(position + sf::Vector2f{ 0, y });
        

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }
    return 0;
}