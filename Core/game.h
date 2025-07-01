#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define GRID_ROWS 100
#define GRID_COLS 75

#define DEAD_CELL 0
#define LIVE_CELL 1

#define PADDING 1.f

#define CELL_SIZE_X ((float)(WINDOW_WIDTH - (GRID_ROWS + 1) * PADDING) / (float)GRID_ROWS)
#define CELL_SIZE_Y ((float)(WINDOW_HEIGHT - (GRID_COLS + 1) * PADDING) / (float)GRID_COLS)

#define INDEX(r, c) ((r) * GRID_COLS + (c))


typedef struct
{
	int row;
	int col;
} GridPosition;
bool SDLInitialization();

void GridInitialization(uint8_t* matrix);
void HandleQuitEvent(SDL_Event event, bool* done);
void GridUpdate(uint8_t* matrix, uint8_t* previous);
int CountLiveNeighbors(uint8_t* matrix, int row, int col);
bool IsAlive(uint8_t* matrix, int row, int col);
void printMatrix(uint8_t* matrix);
void displayMatrix(uint8_t* matrix, SDL_Renderer* renderer, int row, int column);
void RenderMatrix(SDL_Renderer* renderer, uint8_t* matrix);
void GetMousePosition(SDL_Event event, uint8_t* matrix);
GridPosition GetMouseCoordinatesInGrid();
bool IsWitinBound(int row, int col);
void HandleKeyPress(SDL_Event event, uint8_t* matrix, uint8_t* previous, bool* toggleUpdate);
int GetNextGridState(int currentCell, int liveNeighbours);
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void PlacePatternPentomino(uint8_t* matrix);
void PlacePatternRings(uint8_t* matrix);

void PlacePatternReflector(uint8_t* matrix);
void CleanUp();
int GameLoop();

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

