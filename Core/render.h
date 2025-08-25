#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>


#include "config.h"

void displayMatrix(uint8_t* matrix, SDL_Renderer* renderer, int row, int column);

void RenderMatrix(SDL_Renderer* renderer, uint8_t* matrix);
