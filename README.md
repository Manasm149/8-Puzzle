# 8-Puzzle Solver in C++ (A* Algorithm)

This is a C++ program that solves the **8-puzzle** problem using the **A* search algorithm** with the Manhattan distance heuristic.

## 📋 Problem Statement

Given an `n x n` board with numbers from `1` to `n^2 - 1` and a blank space represented as `0`, the goal is to rearrange the board to match the goal state:


## 🚀 Features

- Uses **Manhattan Distance** as the heuristic function.
- Implements **A* Search Algorithm**.
- Uses a twin board to check for **solvability**.
- Prints the entire **solution path** from initial to goal state.
- Shows the **minimum number of moves** required.

## 🧠 Concepts Used

- **A\* Search**: Explores paths with lowest `f(n) = g(n) + h(n)` where:
  - `g(n)` = number of moves made
  - `h(n)` = Manhattan distance (number of moves each tile is away from its goal position)
- **Twin Boards**: Swap two non-zero tiles to detect if the puzzle is unsolvable.
- **Priority Queue**: Used to always explore the lowest-cost node next.
- **Backtracking**: Each node stores a pointer to its parent for reconstructing the solution.

## 🧱 Structure

- `Board.h / Board.cpp`: Represents the puzzle board and operations.
- `Solver.cpp`: Core logic of A* search and solution extraction.
- `main.cpp`: Entry point for reading input and outputting results.

