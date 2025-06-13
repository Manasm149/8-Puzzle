#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

// Board class represents the state of the puzzle
class Board {
private:
    std::vector<std::vector<int>> tiles; // 2D vector of puzzle tiles
    int n; // board dimension

public:
    Board(const std::vector<std::vector<int>>& blocks);
    int dimension() const;
    int manhattan() const; // heuristic function
    bool is_goal() const; // check if current state is the goal
    bool operator==(const Board& other) const;
    std::vector<Board> neighbors() const; // generate valid moves
    Board twin() const; // twin board with two non-empty tiles swapped
    std::string to_string() const; // string representation for printing
    const std::vector<std::vector<int>>& get_tiles() const;
};

#endif
