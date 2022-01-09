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

        int m_screen_width;
        int m_screen_height;

        static int m_score;

        /**
         * @brief Rotates the m_board by counterclockwise 90 degrees
         * 
         * @param repeat The amount of times to repeat the 90 turn
         */
        void rotateBy90(int repeat);
        
        /**
         * @brief Shifts m_board to left most-left
         */
        void shiftLeft();

        /**
         * @brief Merges cells together to the left most block
         */
        void mergeLeft();

        /**
         * @brief Base move class, called by all the movements 
         * 
         * @param _r first rotation
         * @param __r second rotation
         */
        void move(int _r, int __r);
    public: 
        static const int row_size = 4;

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

        /**
         * @brief Spawns a random cell with either a value of 2 or 4 in a random location
         * 
         */
        void spawnRandomCell();

        /**
         * @brief Compares the given board with the member board
         * 
         * @param other_board The board to be compared
         */
        bool isBoardEqual(int** other_board);

        /**
        * @brief Edits the m_board so that all non-zero values move the given moment
        */
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
};