include_directories(../src)

add_executable(
    tests

    test_main.cpp

    test_board.cpp
)
target_link_libraries(
    tests

    board
)
