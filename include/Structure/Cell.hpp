#pragma once

// SFML Includes:
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Cell {
    private:
        int m_value;
        int m_x_pos;
        int m_y_pos;
        sf::Sprite m_sprite;

    public:
    /**
     * @brief the pixel size of each cell
     */
    static int cell_size;
    /**
     * @brief Construct a new Cell object
     * 
     * @param x_pos 
     * @param y_pos 
     */
    Cell(int x_pos, int y_pos, int value);
    
    /**
     * @brief 
     * 
     * @param renderWindow The Window where the object will be drawn
     * @param shapeObj The shape structure that the object will be included in
     * @param shapeIndex The Cell's index within the shapeObj structure
     */
    void draw(sf::RenderWindow& renderWindow);

    sf::Sprite getSprite();
    void setSprite(sf::Sprite s);
};