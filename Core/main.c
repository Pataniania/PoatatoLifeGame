#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "game.h"


int main(int argc, char* argv[]) 
{
    bool done = false;
    bool toggleUpdate = false;

    uint8_t* matrix = malloc(sizeof(uint8_t) * GRID_ROWS * GRID_COLS);
    if (!matrix) 
    {
        SDL_Log("Failed to allocate grid memory");
        return -1;
    }

    uint8_t* previous = malloc(sizeof(uint8_t) * GRID_ROWS * GRID_COLS);
    if (!previous)
    {
        SDL_Log("Failed to allocate grid memory");
        return -1;
    }

    if (!SDLInitialization())
    {
        return -1;
    }

    GridInitialization(matrix);

    while (!done) 
    {
        SDL_Event event;
 
        while (SDL_PollEvent(&event))
        {
            HandleQuitEvent(event, &done);
            GetMousePosition(event, matrix);
            HandleKeyPress(event, matrix, previous, &toggleUpdate);
        }
        if (toggleUpdate)
        {
            GridUpdate(matrix, previous);
            SDL_Delay(100);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        RenderMatrix(renderer, matrix);

        SDL_RenderPresent(renderer);

    }
    free(matrix);
    free(previous);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
