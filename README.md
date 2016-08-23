# cpp-life

## To Build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## To Run
```
cd build
./src/cpp-life
```

Optionally, you can pass a file path as the first argument to load a pattern.
See the patterns directory for a few built-in ones.

### Controls
* `Left Click`: Set or unset cells.
* `Space`: Run the simulation at 5 generations per second.
* `S`: Step the simulation one generation. Can be held down.
* `W`: Save out the current board to board.txt.

## To Run Tests
```
cd build
./test/tests
```
