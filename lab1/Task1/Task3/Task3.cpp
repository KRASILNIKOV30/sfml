#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "House", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(170, 20, 30));
    trapeze.setPosition(400, 200);
    trapeze.setPointCount(4);
    trapeze.setPoint(0, { 200, 0 });
    trapeze.setPoint(1, { 300, 100 });
    trapeze.setPoint(2, { -300, 100 });
    trapeze.setPoint(3, { -200, 0 });

    sf::RectangleShape mainRect({ 500, 300 });
    mainRect.setFillColor(sf::Color(70, 20, 10));
    mainRect.setPosition({ 150, 300 });

    sf::RectangleShape door({ 100, 200 });
    door.setFillColor(sf::Color(10, 10, 10));
    door.setPosition({ 250, 400 });

    sf::RectangleShape rect1({ 50, 100 });
    rect1.setFillColor(sf::Color(20, 20, 20));
    rect1.setPosition({ 450, 150 });

    sf::RectangleShape rect2({ 100, 50 });
    rect2.setFillColor(sf::Color(20, 20, 20));
    rect2.setPosition({ 425, 125 });
    
    sf::CircleShape cr1(30);
    cr1.setFillColor(sf::Color(200, 200, 200));
    cr1.setPosition({ 450, 90 });

    sf::CircleShape cr2(40);
    cr2.setFillColor(sf::Color(200, 200, 200));
    cr2.setPosition({ 480, 45 });

    sf::CircleShape cr3(50);
    cr3.setFillColor(sf::Color(200, 200, 200));
    cr3.setPosition({ 529, 10 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(trapeze);
        window.draw(mainRect);
        window.draw(door);
        window.draw(cr1);
        window.draw(cr2);
        window.draw(cr3);
        window.draw(rect1);
        window.draw(rect2);

        window.display();
    }
    return 0;
}