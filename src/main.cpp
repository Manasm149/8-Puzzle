#include "Board.h"
#include <iostream>
#include "Solver.cpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tiles(n, std::vector<int>(n));

    // Input the initial board configuration
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> tiles[i][j];

    Board initial(tiles);
    Solver solver(initial);
    solver.print_solution();
} 

