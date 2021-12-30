// SFML Includes:
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 2048 Includes:
#include "Structure/Grid.hpp"
#include "Structure/Cell.hpp"

Grid::Grid(int screen_width, int screen_height) {
    m_size = (screen_width * .85); 
    x_pos = ((screen_width - m_size) * .5);
    y_pos = screen_height * .08;

    const int row_size = 4;

    m_board = new int*[row_size];
    
    for (int h = 0; h < row_size; h++) {
        m_board[h] = new int[row_size];
        for (int w = 0; w < row_size; w++) {
            m_board[h][w] = 0;
        }
    }
};

Grid::~Grid() {
    const int row_size = 4;
    for (int h = 0; h < row_size; h++) {
        delete [] m_board[h];
    }
    delete [] m_board;
}

void Grid::draw(sf::RenderWindow& renderWindow) {
    sf::RectangleShape boarder(sf::Vector2f(0, 0));
    boarder.setPosition(sf::Vector2f(x_pos, y_pos));
    boarder.setSize(sf::Vector2f(m_size, m_size));

    boarder.setFillColor(sf::Color(150, 150, 150));

    renderWindow.draw(boarder);


    const int row_size = 4;
    const float margin_size = (m_size - (Cell::cell_size * row_size)) / (row_size + 1);

    for (int row = 0; row < row_size; row++) {
        for (int col = 0; col < row_size; col++) {
            
            int _x_pos = x_pos + ((col + 1) * margin_size) + (col * Cell::cell_size);
            int _y_pos = y_pos + ((row + 1) * margin_size) + (row * Cell::cell_size);

            Cell c(_x_pos, _y_pos, m_board[row][col]);
            c.draw(renderWindow);
        }
    }

}

int ** Grid::getBoard() {
    return m_board;
}

void Grid::setCell(int row, int col, int value) {
    m_board[row][col] = value;
}