#include "Board.h"
#include <iostream>
#include <queue>
#include <set>
#include <memory>

// Node represents a state in the A* search tree
struct Node {
    Board board;
    int moves;
    int priority;
    std::shared_ptr<Node> prev; // previous state (for path reconstruction)

    Node(Board b, int m, std::shared_ptr<Node> p)
        : board(std::move(b)), moves(m), prev(std::move(p)) {
        priority = board.manhattan() + moves; // A* cost = g + h
    }

    bool operator>(const Node& other) const {
        return priority > other.priority;
    }
};

class Solver {
private:
    bool solvable;
    std::shared_ptr<Node> solution_node;

public:
    Solver(const Board& initial);
    bool is_solvable() const;
    int moves() const;
    void print_solution() const;
};

Solver::Solver(const Board& initial) {
    using PNode = std::shared_ptr<Node>;
    auto cmp = [](const PNode& a, const PNode& b) { return *a > *b; };

    std::priority_queue<PNode, std::vector<PNode>, decltype(cmp)> pq(cmp);
    std::priority_queue<PNode, std::vector<PNode>, decltype(cmp)> twin_pq(cmp);

    // start from initial and its twin (for solvability check)
    pq.push(std::make_shared<Node>(initial, 0, nullptr));
    twin_pq.push(std::make_shared<Node>(initial.twin(), 0, nullptr));

    while (true) {
        auto current = pq.top(); pq.pop();
        auto twin = twin_pq.top(); twin_pq.pop();

        if (current->board.is_goal()) {
            solvable = true;
            solution_node = current;
            break;
        }

        if (twin->board.is_goal()) {
            solvable = false;
            break;
        }

        // expand current node
        for (const auto& neighbor : current->board.neighbors()) {
            if (!current->prev || neighbor != current->prev->board)
                pq.push(std::make_shared<Node>(neighbor, current->moves + 1, current));
        }

        // expand twin
        for (const auto& neighbor : twin->board.neighbors()) {
            if (!twin->prev || neighbor != twin->prev->board)
                twin_pq.push(std::make_shared<Node>(neighbor, twin->moves + 1, twin));
        }
    }
}

bool Solver::is_solvable() const {
    return solvable;
}

int Solver::moves() const {
    return solvable ? solution_node->moves : -1;
}

void Solver::print_solution() const {
    if (!solvable) {
        std::cout << "No solution possible\n";
        return;
    }

    std::vector<Board> path;
    for (auto node = solution_node; node; node = node->prev)
        path.push_back(node->board);

    std::reverse(path.begin(), path.end());
    std::cout << "Minimum number of moves = " << moves() << "\n";
    for (const auto& board : path)
        std::cout << board.to_string() << "\n";
}
