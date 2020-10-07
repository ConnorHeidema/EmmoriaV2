// #include "util/Size.hpp"

// #include "core/Application.hpp"
// #include "config/ConfigItems.hpp"

// #include <SFML/Graphics.hpp>

// #include <iostream>

// int main() {
// 	Application app;
//     ConfigItems::LoadConfigFile("data/Config/config.ini");
//     app.Start() ?
//         std::cout << "Successfully exited game." :
//         std::cout << "Error occurred while exiting game";
// }
#include <SFML/Graphics.hpp>

#include <math.h>

#include <iostream>



int main()
{
    std::cout << sin(3.14159265) << std::endl;
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML rect rotation");
    float angle(0.f);
    while (App.isOpen())
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                App.close();
        }
        App.clear();
        double topLeftX = 300;
        double topLeftY = 300;

        double width = 100;
        double height = 100;

        double xPositionAxis = std::sqrt(std::pow(width, 2) + std::pow(width, 2));
        double yPositionAxis = std::sqrt(std::pow(height, 2) + std::pow(height, 2));
        double offset = 3.1415926535 / 2;
        auto thing = sf::RectangleShape(sf::Vector2f(width, height));

        double rectAngle = atan2(height, width);
        std::cout << rectAngle << std::endl;
        double xLoc = (sin(rectAngle) + sin(-rectAngle + angle * 3.1415928/180)) * xPositionAxis / 2;
        double yLoc = (sin(rectAngle - 3*offset) + sin(-rectAngle + 3*offset + angle * 3.1415928/180)) * yPositionAxis / 2;

        thing.setPosition(topLeftX + xLoc, topLeftY + yLoc);

        thing.rotate(angle);

        App.draw(thing);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            angle += 0.1;
            std::cout << angle << std::endl;
        }

        auto thing2 = sf::RectangleShape(sf::Vector2f(6,6));
        thing2.setPosition(297, 297);
        thing2.setFillColor(sf::Color::Blue);
        App.draw(thing2);

        App.display();
    }
}
