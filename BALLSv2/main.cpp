#include <iostream>
#include <SFML/Graphics.hpp>
#include "solver.h"

#define WIDTH 1024
#define HEIGHT 1024

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Balls");
    window.setFramerateLimit(240);

    sf::Clock clock;
    float deltaTime;

    float constraintRadius = 400;
    sf::CircleShape constraint{ constraintRadius, 120};
    constraint.setOrigin(constraintRadius, constraintRadius);
    constraint.setFillColor(sf::Color::Black);
    constraint.setPosition(WIDTH / 2, HEIGHT / 2);

    Solver solver;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) solver.addBall(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            solver.addBall(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }

        deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color(50, 50, 50, 255));

        window.draw(constraint);

        solver.update(deltaTime, 10);
        for (auto ball : solver.Balls) {
            ball.drawTo(window);
        }

        
        window.display();
    }

    return 0;
}
