hunter_add_package(SDL2)

find_package(SDL2)

add_library(
    board
    STATIC

    board.cpp
)
set_property(TARGET board PROPERTY CXX_STANDARD 11)

add_executable(
    cpp-life

    main.cpp
    nuklear.cpp
)
target_link_libraries(
    cpp-life

    board
    SDL2
)
set_property(TARGET cpp-life PROPERTY CXX_STANDARD 11)
set_property(TARGET cpp-life APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)
