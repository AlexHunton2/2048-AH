// C++ Includes:
#include <math.h> 
#include <string> 

// SFML Includes:
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

// 2048 Includes
#include "Structure/Cell.hpp"

Cell::Cell(int x_pos, int y_pos, int value) {
    m_value = value;
    m_x_pos = x_pos;
    m_y_pos = y_pos;

    sf::Texture texture;
    texture.create(cell_size, cell_size);

    sf::Sprite s = this->getSprite();

    s.setTexture(texture);
    s.setTextureRect(sf::IntRect(0, 0, Cell::cell_size, Cell::cell_size));
    
    s.setPosition(x_pos, y_pos);

    if (m_value > 0) {
        s.setColor(sf::Color(150 - (log2(m_value) * 10), 150 - (log2(m_value) * 10), 255, 50 + log2(m_value) * 15));
    } else {
        s.setColor(sf::Color(170, 170, 170));
    }
    this->setSprite(s);
}

void Cell::draw(sf::RenderWindow& renderWindow) {
    renderWindow.draw(this->getSprite());  

    if (m_value > 0) {
        sf::Font font;
        if (!font.loadFromFile("../src/Fonts/arial.ttf")) {}

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(m_value));
        text.setCharacterSize(75); 
        text.setFillColor(sf::Color(0, 0, 0));
        text.setStyle(sf::Text::Bold);
        text.setOrigin(text.getLocalBounds().width/2. , text.getLocalBounds().height/2.);
        text.setPosition(sf::Vector2f((m_x_pos + Cell::cell_size / 2) - 5, (m_y_pos + Cell::cell_size / 2) - 20));
        renderWindow.draw(text);
    }
    
}

sf::Sprite Cell::getSprite() {
    return m_sprite;
}

void Cell::setSprite(sf::Sprite s) {
    m_sprite = s;
}