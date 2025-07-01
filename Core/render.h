#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

void displayMatrix(uint8_t* matrix, SDL_Renderer* renderer, int row, int column);

void RenderMatrix(SDL_Renderer* renderer, uint8_t* matrix);

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
