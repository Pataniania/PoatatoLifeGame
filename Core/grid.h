#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>


#include "config.h"


void GridInitialization(uint8_t* matrix);

void GridUpdate(uint8_t* matrix, uint8_t* previous);

int CountLiveNeighbors(uint8_t* matrix, int row, int col);

int GetNextGridState(int currentCell, int liveNeighbours);

bool IsAlive(uint8_t* matrix, int row, int col);






