cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.15.17.tar.gz"
    SHA1 "c1b386f70faaed31ede20aa421282087ebb1ee5f"
)

project(cpp-life)

add_subdirectory(src)
add_subdirectory(test)
