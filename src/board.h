#pragma once

#include <array>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using std::uint8_t;
using std::int64_t;


typedef std::pair<int64_t, int64_t> Cell;

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
    template<>
    struct hash<Cell> {
        size_t operator()(Cell const& cell) const {
            size_t seed = 0;
            hash_combine(seed, cell.first);
            hash_combine(seed, cell.second);

            return seed;
        }
    };
}

// TODO: Consider implementing own cell?
//struct Cell {
//    int64_t x;
//    int64_t y;
//};

class LifeBoard {
    public:
        LifeBoard();

        uint8_t get_neighbor_count(int64_t x, int64_t y) const;
        bool get(int64_t x, int64_t y) const;
        void set(int64_t x, int64_t y, bool value);
        void clear();
        void step();

        size_t live_cell_count() const;

        typedef std::unordered_set<Cell>::const_iterator const_iterator;
        const_iterator begin() const;
        const_iterator end() const;

    private:
        std::array<Cell, 8> get_neighbors(int64_t x, int64_t y);
        void update_neighbors(int64_t x, int64_t y, bool value);

        std::unordered_set<Cell> alive;
        std::unordered_map<Cell, uint8_t> neighbors;
};
