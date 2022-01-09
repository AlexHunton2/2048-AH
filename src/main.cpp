//Standard Library
#include <iostream>
#include <vector>

// SFML Includes:
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 2048 Includes
#include <Structure/Grid.hpp>

int main() {
    const int WIDTH = 1280;
    const int HEIGHT = 1224;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2048", sf::Style::Close | sf::Style::Titlebar);

    Grid grid(WIDTH, HEIGHT);

    grid.spawnRandomCell();
    grid.spawnRandomCell();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                // key pressed
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        grid.moveLeft();
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        grid.moveRight();
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        grid.moveUp();
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        grid.moveDown();
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::White);

        grid.draw(window);

        window.display();
    }

    return 0;
}