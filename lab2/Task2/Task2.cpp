#include <SFML/Graphics.hpp>
#include <vector>

void AddRect(float x, float y, float len, float rotate, std::vector<sf::RectangleShape>& shapes)
{
    sf::RectangleShape rect(sf::Vector2f(len, 20));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Yellow);
    rect.setRotation(rotate);
    shapes.push_back(rect);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Initials", sf::Style::Default);

    window.setVerticalSyncEnabled(true);
    std::vector<sf::RectangleShape> shapes;

    //Б
    AddRect(50, 50, 150, 0, shapes);
    AddRect(50, 150, 150, 0, shapes);
    AddRect(50, 230, 150, 0, shapes);
    AddRect(50, 50, 200, 90, shapes);
    AddRect(200, 150, 100, 90, shapes);

    //Я
    AddRect(250, 50, 150, 0, shapes);
    AddRect(270, 50, 100, 90, shapes);
    AddRect(250, 150, 150, 0, shapes);
    AddRect(400, 50, 200, 90, shapes);
    AddRect(340, 170, 110, 130, shapes);

    //К
    AddRect(470, 50, 200, 90, shapes);
    AddRect(450, 150, 135, 315, shapes);
    AddRect(470, 150, 125, 45, shapes);

   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (auto& shape : shapes)
        {
            window.draw(shape);
        }
        window.display();
    }
    return 0;
}