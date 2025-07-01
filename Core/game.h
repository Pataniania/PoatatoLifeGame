#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>


#include "config.h"
#include "render.h"
#include "grid.h"
#include "input.h"

bool SDLInitialization();
void CleanUp();
int GameLoop();

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

