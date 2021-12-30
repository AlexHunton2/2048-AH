#pragma once

// SFML Includes:
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief The grid class. This is what the main class will interface with.
 */
class Grid {
    private:
        float m_size;
        float x_pos;
        float y_pos;
        int** m_board;

    public: 
        /**
         * @brief Construct a new Grid object
         * 
         * @param screen_width the width of the screen
         * @param screen_height the height of the screen
         */
        Grid(int screen_width, int screen_height);

        /**
         * @brief Destroy the Grid object
         */
        ~Grid();

        /**
         * @brief Called every frame. Should be used for drawing the actual frame
         */
        void draw(sf::RenderWindow& renderWindow);

        /**
         * @brief Gets the representation of the grid as an array
         *
         * @return int* 4 by 4 array with the value of the cell
         */
        int ** getBoard();

        /**
         * @brief Sets a cell to the grid at the given row and col
         * 
         * @param row the row position of the new cell
         * @param col the col position of the new cell
         * @param value the value of the new cell
         */
        void setCell(int row, int col, int value);
};