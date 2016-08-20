#include <array>
#include <cstdint>
#include <cstdio>

#include <SDL2/SDL.h>

#include "board.h"

using std::uint32_t;
using std::uint64_t;


const uint32_t SCREEN_WIDTH = 500;
const uint32_t SCREEN_HEIGHT = 500;

const uint64_t BOARD_WIDTH = 50;
const uint64_t BOARD_HEIGHT = 50;

const uint32_t CELL_WIDTH = SCREEN_WIDTH / BOARD_WIDTH;
const uint32_t CELL_HEIGHT = SCREEN_HEIGHT / BOARD_HEIGHT;

const uint32_t FPS = 60;
const uint32_t MS_PER_FRAME = 1000 / FPS;

const std::array<uint8_t, 3> BLACK = {{0, 0, 0}};
const std::array<uint8_t, 3> WHITE = {{255, 255, 255}};


void draw_board(SDL_Renderer* renderer, const LifeBoard& board) {
    SDL_SetRenderDrawColor(renderer, WHITE[0], WHITE[1], WHITE[2], 0);

    SDL_Rect rect;
    for (const Cell& cell: board) {
        rect.x = cell.first * CELL_WIDTH;
        rect.y = cell.second * CELL_HEIGHT;
        rect.w = CELL_WIDTH;
        rect.h = CELL_HEIGHT;
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char** argv) {
    LifeBoard board;

    // Try to load a pattern from a file.
    if (argc == 2) {
        printf("Loading pattern from: %s\n", argv[1]);
        FILE* f = fopen(argv[1], "r");
        uint64_t x, y;
        while (fscanf(f, "(%lld, %lld)\n", &x, &y) == 2) {
            printf("Setting (%llu, %llu)\n", x, y);
            board.set(x, y, true);
        }
    } else if (argc > 2) {
        printf("Too many arguments\n\nUsage:\ncpp-life [file]\n");
        return 0;
    }

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    window = SDL_CreateWindow("cpp-life",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //renderer.set_blend_mode(BlendBlend);

    const uint32_t step_time_ms = 200;

    bool running = true;
    bool simulate = false;
    uint32_t last_step_time = SDL_GetTicks();

    SDL_Event event;
    while (running) {
        uint32_t start_time = SDL_GetTicks();

        // Handle events and input
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    //printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_SPACE:
                            simulate = !simulate;
                            break;
                        case SDLK_c:
                            board.clear();
                            break;
                        case SDLK_s:
                            board.step();
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            board.set(event.button.x / CELL_WIDTH, event.button.y / CELL_HEIGHT, true);
                            break;
                        case SDL_BUTTON_RIGHT:
                            board.set(event.button.x / CELL_WIDTH, event.button.y / CELL_HEIGHT, false);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        // Step the board
        uint32_t current_time = SDL_GetTicks();
        if (simulate && (current_time - last_step_time >= step_time_ms)) {
            board.step();
            last_step_time = SDL_GetTicks();
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, BLACK[0], BLACK[1], BLACK[2], 0);
        SDL_RenderClear(renderer);

        // Draw the board
        draw_board(renderer, board);

        // Update buffers
        SDL_RenderPresent(renderer);

        // Sleep until the next frame
        uint32_t elapsed_time = SDL_GetTicks() - start_time;
        if (elapsed_time < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - elapsed_time);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
