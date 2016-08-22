#include "board.h"

#include <vector>


LifeBoard::LifeBoard() {
}

std::array<Cell, 8> LifeBoard::get_neighbors(int64_t x, int64_t y) {
    std::array<Cell, 8> cell_neighbors;
    int next_neighbor = 0;

    for (int64_t j = y - 1; j < y + 2; j++) {
        for (int64_t i = x - 1; i < x + 2; i++) {
            if (x != i || y != j) {
                cell_neighbors[next_neighbor] = Cell(i, j);
                next_neighbor += 1;
            }
        }
    }
    return cell_neighbors;
}

void LifeBoard::update_neighbors(int64_t x, int64_t y, bool value) {
    auto cell_neighbors = get_neighbors(x, y);
    int amount = value ? 1 : -1 ;

    for (const Cell& cell: cell_neighbors) {
        int neighbor_count = 0;
        auto search = neighbors.find(cell);
        if (search != neighbors.cend()) {
            neighbor_count = search->second;
        }
        int new_neighbor_count = neighbor_count + amount;

        if (new_neighbor_count != 0) {
            neighbors[cell] = new_neighbor_count;
        } else {
            neighbors.erase(cell);
        }
    }
}

uint8_t LifeBoard::get_neighbor_count(int64_t x, int64_t y) const {
    auto search = neighbors.find(Cell(x, y));
    if (search != neighbors.cend()) {
        return search->second;
    }
    return 0;
}

bool LifeBoard::get(int64_t x, int64_t y) const {
    return alive.find(Cell(x, y)) != alive.cend();
}

void LifeBoard::set(int64_t x, int64_t y, bool value) {
    if (value) {
        auto ret = alive.emplace(x, y);
        if (ret.second) {
            update_neighbors(x, y, value);
        }
    } else {
        auto num_removed = alive.erase(Cell(x, y));
        if (num_removed > 0) {
            update_neighbors(x, y, value);
        }
    }
}

void LifeBoard::clear() {
    alive.clear();
    neighbors.clear();
}

void LifeBoard::step() {
    std::vector<Cell> killed;
    std::vector<Cell> spawned;

    for (const Cell& cell: alive) {
        uint8_t neighbor_count = 0;
        auto search = neighbors.find(cell);
        if (search != neighbors.cend()) {
            neighbor_count = search->second;
        }

        if (neighbor_count < 2 || neighbor_count > 3) {
            killed.push_back(cell);
        }
    }

    for (const auto& item: neighbors) {
        if (item.second == 3 && alive.count(item.first) == 0) {
            spawned.push_back(item.first);
        }
    }

    for (const Cell& cell: killed) {
        set(cell.first, cell.second, false);
    }
    for (const Cell& cell: spawned) {
        set(cell.first, cell.second, true);
    }
}

size_t LifeBoard::live_cell_count() const {
    return alive.size();
}

LifeBoard::const_iterator LifeBoard::begin() const {
    return alive.cbegin();
}

LifeBoard::const_iterator LifeBoard::end() const {
    return alive.cend();
}
