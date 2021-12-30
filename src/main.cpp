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
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        Grid grid(WIDTH, HEIGHT);

        grid.setCell(0, 0, 16);
        grid.setCell(2, 3, 1024);

        grid.draw(window);

        window.display();
    }

    return 0;
}