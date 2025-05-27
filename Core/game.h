#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 900

#define GRID_WIDTH 100
#define GRID_HEIGHT 100

#define DEAD_CELL 0
#define LIVE_CELL 1

typedef struct GameArray
{
	int** matrix[GRID_WIDTH][GRID_HEIGHT];

}GameArray;


int SDLInitialization();

int GridInitialization(int matrix[][GRID_HEIGHT]);
void HandleQuitEvent(SDL_Event event, bool done);

void GridUpdate(int matrix[][GRID_HEIGHT]);

int CountLiveNeighbors(int matrix[][GRID_HEIGHT], int row, int col);

int AllocateMatrix();

bool IsAlive(int matrix[][GRID_HEIGHT], int row, int col);

void printMatrix();
//int placingCells(int** matrix);
//int updateManager(int** matrix);
//void checkForNeighbors(int** matrix);
//void updateMatrix(int** matrix);


extern SDL_Window* window;
extern SDL_Renderer* renderer;
int gameArr[GRID_WIDTH][GRID_HEIGHT];
extern int nextMatrix[GRID_WIDTH][GRID_HEIGHT];
extern GameArray* gameArray;

