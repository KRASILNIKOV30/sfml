#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 800), L"Новый проект", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    sf::RectangleShape rectangle(sf::Vector2f(200, 620));
    rectangle.setPosition(100, 90);
    rectangle.setFillColor(sf::Color::Black);

    std::vector<sf::CircleShape> circles;

    for (int i = 0; i < 3; i++)
    {
        sf::CircleShape circle(80);
        circle.setPosition(120, 120 + 200 * i);
        circles.push_back(circle);
    }

    circles[0].setFillColor(sf::Color::Red);
    circles[1].setFillColor(sf::Color::Yellow);
    circles[2].setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(rectangle);
        for (auto& circle : circles)
        {
            window.draw(circle);
        }
        window.display();
    }
    return 0;
}