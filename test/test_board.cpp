#include "catch.hpp"

#include "board.h"


TEST_CASE("Set and get one cell", "[set_get_one_cell]") {
    LifeBoard board;

    board.set(1, 1, true);

    REQUIRE(board.get(1, 1) == true);
}

TEST_CASE("Step board with one cell", "[step_one_cell]") {
    LifeBoard board;

    board.set(1, 1, true);

    REQUIRE(board.get(1, 1) == true);

    board.step();

    REQUIRE(board.get(1, 1) == false);
}

TEST_CASE("Set cell and check neighbors", "[update_neighbors_increment]") {
    LifeBoard board;

    board.set(1, 1, true);

    REQUIRE(board.get_neighbor_count(0, 0) == 1);
    REQUIRE(board.get_neighbor_count(1, 0) == 1);
    REQUIRE(board.get_neighbor_count(2, 0) == 1);
    REQUIRE(board.get_neighbor_count(0, 1) == 1);
    REQUIRE(board.get_neighbor_count(1, 1) == 0);
    REQUIRE(board.get_neighbor_count(2, 1) == 1);
    REQUIRE(board.get_neighbor_count(0, 2) == 1);
    REQUIRE(board.get_neighbor_count(1, 2) == 1);
    REQUIRE(board.get_neighbor_count(2, 2) == 1);
}

TEST_CASE("Set and unset cell and check neighbors", "[update_neighbors_increment_decrement]") {
    LifeBoard board;

    board.set(1, 1, true);

    REQUIRE(board.get_neighbor_count(0, 0) == 1);
    REQUIRE(board.get_neighbor_count(1, 0) == 1);
    REQUIRE(board.get_neighbor_count(2, 0) == 1);
    REQUIRE(board.get_neighbor_count(0, 1) == 1);
    REQUIRE(board.get_neighbor_count(1, 1) == 0);
    REQUIRE(board.get_neighbor_count(2, 1) == 1);
    REQUIRE(board.get_neighbor_count(0, 2) == 1);
    REQUIRE(board.get_neighbor_count(1, 2) == 1);
    REQUIRE(board.get_neighbor_count(2, 2) == 1);

    board.set(1, 1, false);

    REQUIRE(board.get_neighbor_count(0, 0) == 0);
    REQUIRE(board.get_neighbor_count(1, 0) == 0);
    REQUIRE(board.get_neighbor_count(2, 0) == 0);
    REQUIRE(board.get_neighbor_count(0, 1) == 0);
    REQUIRE(board.get_neighbor_count(1, 1) == 0);
    REQUIRE(board.get_neighbor_count(2, 1) == 0);
    REQUIRE(board.get_neighbor_count(0, 2) == 0);
    REQUIRE(board.get_neighbor_count(1, 2) == 0);
    REQUIRE(board.get_neighbor_count(2, 2) == 0);
}

TEST_CASE("Set cell and iterate", "[iter_live_cells]") {
    LifeBoard board;

    board.set(1, 1, true);

    REQUIRE(board.begin() != board.end());
    REQUIRE(*(board.begin()) == Cell(1, 1));
}
