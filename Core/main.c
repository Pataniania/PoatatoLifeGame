#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>



#include "grid.h"
#include "game.h"


int main() {

    bool done = false;
    int matrix[GRID_WIDTH][GRID_HEIGHT] = {0};

    if (SDLInitialization() != 0)
    {
        return -1;
    }

    GridInitialization(matrix);

    while (!done) 
    {
        GridUpdate(matrix);
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            HandleQuitEvent(event, done);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        RenderDrawGrid(renderer);

        SDL_RenderPresent(renderer);


        //cursor_position();
        //draw_grid(renderer);
        //draw_cursor(renderer);
        ////SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderPresent(renderer);
        //SDL_Delay(10);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
