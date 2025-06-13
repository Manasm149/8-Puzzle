#include "Board.h"
#include <sstream>
#include <algorithm>

Board::Board(const std::vector<std::vector<int>>& blocks) : tiles(blocks), n(blocks.size()) {}

int Board::dimension() const {
    return n;
}

int Board::manhattan() const {
    int dist = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (tiles[i][j] && tiles[i][j] != i * n + j + 1)
                dist += abs(i - (tiles[i][j] - 1) / n) + abs(j - (tiles[i][j] - 1) % n);
    return dist;
}

bool Board::is_goal() const {
    int expected = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j, ++expected)
            if (tiles[i][j] != (expected % (n * n))) return false;
    return true;
}

bool Board::operator==(const Board& other) const {
    return tiles == other.tiles;
}

std::vector<Board> Board::neighbors() const {
    std::vector<Board> res;
    int blank_i, blank_j;
    // find the empty tile
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (tiles[i][j] == 0) { blank_i = i; blank_j = j; }

    const int dx[] = { -1, 1, 0, 0 }; // directions
    const int dy[] = { 0, 0, -1, 1 };

    // explore all valid directions
    for (int d = 0; d < 4; ++d) {
        int ni = blank_i + dx[d];
        int nj = blank_j + dy[d];
        if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
            auto new_tiles = tiles;
            std::swap(new_tiles[blank_i][blank_j], new_tiles[ni][nj]);
            res.push_back(Board(new_tiles));
        }
    }

    return res;
}

Board Board::twin() const {
    auto new_tiles = tiles;
    // swap any two non-zero tiles to form a twin board
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n - 1; ++j)
            if (new_tiles[i][j] && new_tiles[i][j + 1]) {
                std::swap(new_tiles[i][j], new_tiles[i][j + 1]);
                return Board(new_tiles);
            }
    return *this; // fallback
}

std::string Board::to_string() const {
    std::ostringstream oss;
    oss << n << "\n";
    for (const auto& row : tiles) {
        for (int tile : row) oss << tile << " ";
        oss << "\n";
    }
    return oss.str();
}

const std::vector<std::vector<int>>& Board::get_tiles() const {
    return tiles;
}
