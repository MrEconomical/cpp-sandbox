#include <chrono>
#include <iostream>
#include <thread>

class GameOfLife {
    static const size_t ROWS = 15;
    static const size_t COLS = 30;
    static const double INITIAL_CHANCE;

    bool cells[ROWS * COLS];
    bool buffer[ROWS * COLS];
    int generation;

public:
    GameOfLife(): cells{}, buffer{}, generation{} {
        // Populate initial cells with random chance

        for (size_t r = 1; r < ROWS - 1; r ++) {
            for (size_t c = 1; c < COLS - 1; c ++) {
                double roll = static_cast<double>(std::rand()) / RAND_MAX;
                if (roll < INITIAL_CHANCE) {
                    cells[r * COLS + c] = true;
                    buffer[r * COLS + c] = true;
                }
            }
        }
    }

    void advance() {
        // Repopulate buffer grid by game of life rules

        for (size_t r = 1; r < ROWS - 1; r ++) {
            for (size_t c = 1; c < COLS - 1; c ++) {
                // Calculate neighbor count

                int neighbors = (cells[(r - 1) * COLS + c - 1] ? 1 : 0)
                    + (cells[(r - 1) * COLS + c] ? 1 : 0)
                    + (cells[(r - 1) * COLS + c + 1] ? 1 : 0)
                    + (cells[r * COLS + c - 1] ? 1 : 0)
                    + (cells[r * COLS + c + 1] ? 1 : 0)
                    + (cells[(r + 1) * COLS + c - 1] ? 1 : 0)
                    + (cells[(r + 1) * COLS + c] ? 1 : 0)
                    + (cells[(r + 1) * COLS + c + 1] ? 1 : 0);

                // Apply game of life rules
                
                if (!cells[r * COLS + c]) {
                    if (neighbors == 3) {
                        buffer[r * COLS + c] = true;
                    }
                } else {
                    if (neighbors != 2 && neighbors != 3) {
                        buffer[r * COLS + c] = false;
                    }
                }
            }
        }

        // Copy buffer grid to original grid

        for (size_t r = 1; r < ROWS - 1; r ++) {
            for (size_t c = 1; c < COLS - 1; c ++) {
                cells[r * COLS + c] = buffer[r * COLS + c];
            }
        }

        // Increment generation

        generation ++;
    }

    void display() {
        std::system("cls");
        std::cout << "Generation " << generation << std::endl;
        for (size_t r = 0; r < ROWS; r ++) {
            for (size_t c = 0; c < COLS; c ++) {
                std::cout << (cells[r * COLS + c] ? "X" : ".");
            }
            std::cout << std::endl;
        }
    }
};

const double GameOfLife::INITIAL_CHANCE = 0.4;

int main() {
    // Create game

    GameOfLife game = GameOfLife();

    // Run game loop

    while (true) {
        game.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        game.advance();
    }
}