#pragma once

#include <SDL3/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"
#include "grid.h"


typedef struct
{
	int row;
	int col;
} GridPosition;

void HandleQuitEvent(SDL_Event event, bool* done);

void GetMousePosition(SDL_Event event, uint8_t* matrix);

void HandleKeyPress(SDL_Event event, uint8_t* matrix, uint8_t* previous, bool* toggleUpdate);

GridPosition GetMouseCoordinatesInGrid();

bool IsWitinBound(int row, int col);

void PlacePatternPentomino(uint8_t* matrix);

void PlacePatternRings(uint8_t* matrix);

void PlacePatternReflector(uint8_t* matrix);
