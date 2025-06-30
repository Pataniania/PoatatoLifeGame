#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>



#include "grid.h"
#include "game.h"


int main(int argc, char* argv[]) 
{


    bool done = false;
    int matrix[GRID_WIDTH][GRID_HEIGHT] = {0};

    if (SDLInitialization() != 0)
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
            HandleKeyPress(event, matrix);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        RenderMatrix(renderer, matrix);
        //RenderDrawGrid(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
