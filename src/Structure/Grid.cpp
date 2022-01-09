// Standard Library Includes:
#include <stdlib.h> 

// SFML Includes:
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 2048 Includes:
#include "Structure/Grid.hpp"
#include "Structure/Cell.hpp"

int Grid::m_score = 0;

Grid::Grid(int screen_width, int screen_height) {
    m_screen_width = screen_width;
    m_screen_height = screen_height;

    m_size = (screen_width * .85); 
    x_pos = ((screen_width - m_size) * .5);
    y_pos = screen_height * .08;

    m_board = new int*[row_size];
    
    for (int h = 0; h < row_size; h++) {
        m_board[h] = new int[row_size];
        for (int w = 0; w < row_size; w++) {
            m_board[h][w] = 0;
        }
    }
};

Grid::~Grid() {
    for (int h = 0; h < row_size; h++) {
        delete [] m_board[h];
    }
    delete [] m_board;
}

void Grid::draw(sf::RenderWindow& renderWindow) {
    sf::RectangleShape border(sf::Vector2f(0, 0));
    border.setPosition(sf::Vector2f(x_pos, y_pos));
    border.setSize(sf::Vector2f(m_size, m_size));

    border.setFillColor(sf::Color(150, 150, 150));

    renderWindow.draw(border);

    const float magic_border_cell_ratio = .85;
    Cell::cell_size = (m_size / row_size) * magic_border_cell_ratio;
    const float margin_size = (m_size - (Cell::cell_size * row_size)) / (row_size + 1);

    // Draw Score and Title
    sf::Font font;
    if (!font.loadFromFile("../src/Fonts/arial.ttf")) {}

    sf::Text title;
    title.setFont(font);
    title.setString("2048");
    title.setCharacterSize(75); 
    title.setFillColor(sf::Color(0, 0, 0));
    title.setStyle(sf::Text::Bold);
    title.setOrigin(0. , title.getLocalBounds().height/2.);
    title.setPosition(sf::Vector2f(margin_size + 80, 30));
    renderWindow.draw(title);

    std::string tmp = std::to_string(m_score);

    char SCORE_STRING[9] = "Score: ";
    const char * score_str = tmp.c_str();

    sf::Text score;
    score.setFont(font);
    score.setString(strcat(SCORE_STRING, score_str));
    score.setCharacterSize(75); 
    score.setFillColor(sf::Color(0, 0, 0));
    score.setStyle(sf::Text::Bold);
    score.setOrigin(0. , score.getLocalBounds().height/2.);
    score.setPosition(sf::Vector2f(m_screen_width - (margin_size + 500), 30));
    renderWindow.draw(score);


    for (int row = 0; row < row_size; row++) {
        for (int col = 0; col < row_size; col++) {
            
            int _x_pos = x_pos + ((col + 1) * margin_size) + (col * Cell::cell_size);
            int _y_pos = y_pos + ((row + 1) * margin_size) + (row * Cell::cell_size);

            Cell c(_x_pos, _y_pos, m_board[row][col]);
            c.draw(renderWindow);
        }
    }

}

void Grid::rotateBy90(int repeat) {
    for (int r = 0; r < repeat; r++) {
        // create empty board
        int ** new_board = new int*[row_size];
        for(int i = 0; i < row_size; ++i) {
            new_board[i] = new int[row_size];
            for (int j = 0; j < row_size; j++) {
                new_board[i][j] = 0;
            }
        }
        
        // perform 90 rotation on new_board
        for (int row = 0; row < row_size; row++) {
            for (int col = 0; col < row_size; col++) {
                new_board[(row_size - 1) - col][row] = m_board[row][col];
            }
        }

        // free old board memory
        for (int h = 0; h < row_size; h++) {
            delete [] m_board[h];
        }
        delete [] m_board;

        // assign board pointer to the newly update memory 
        m_board = new_board;
    }
}

void Grid::shiftLeft() {
    // move all to left
    for (int row = 0; row < row_size; row++) {
        for (int col = 1; col < row_size; col++) {
            if (m_board[row][col] > 0) {
                int i = col;
                while (true) {
                    if (m_board[row][i-1] == 0 && i > 0) {
                        m_board[row][i-1] = m_board[row][i];
                        m_board[row][i] = 0;
                        i--;
                    } else {
                        break;
                    }
                }
            }
        }
    } 
}

void Grid::mergeLeft() {
    for (int row = 0; row < row_size; row++) {
        for (int col = 1; col < row_size; col++) {
            if (m_board[row][col] == m_board[row][col-1]) {
                m_board[row][col-1] = m_board[row][col] * 2;
                m_score += m_board[row][col] * 2;
                m_board[row][col] = 0;
            }
        }
    }
}

void Grid::move(int _r, int __r) {
    int ** old_board = new int*[row_size];
    for(int i = 0; i < row_size; ++i) {
        old_board[i] = new int[row_size];
        for (int j = 0; j < row_size; j++) {
            old_board[i][j] = m_board[i][j];
        }
    }

    // transformations
    rotateBy90(_r);
    shiftLeft();
    mergeLeft();
    shiftLeft();
    rotateBy90(__r);

    //check if transmortion changed anything
    if (!isBoardEqual(old_board)) {
        spawnRandomCell();
    }
}

void Grid::moveLeft() {
    move(0, 0);
}

void Grid::moveRight() {
    move(2, 2);
}

void Grid::moveUp() {
    move(1, 3);
}

void Grid::moveDown() {
    move(3, 1);
}

void Grid::spawnRandomCell() {
    srand(time(NULL));
    while (true) {
        int value = (rand() % 2 + 1) * 2;
        int _x = rand() % Grid::row_size;
        int _y = rand() % Grid::row_size;
        if (m_board[_x][_y] == 0) {
            setCell(_x, _y, value);
            break;
        }
    }
}

bool Grid::isBoardEqual(int** other_board) {
    for (int row = 0; row < row_size; row++) {
        for (int col = 0; col < row_size; col++) {
            if (other_board[row][col] != m_board[row][col]) {
                return false;
            }
        }
    }

    return true;
}

int ** Grid::getBoard() {
    return m_board;
}

void Grid::setCell(int row, int col, int value) {
    m_board[row][col] = value;
}