#include "render.h"


void displayMatrix(uint8_t* matrix, SDL_Renderer* renderer, int row, int column)
{
	SDL_FRect cell = { column * (CELL_SIZE_X + PADDING), row * (CELL_SIZE_Y + PADDING), CELL_SIZE_X, CELL_SIZE_Y };

	if (matrix[INDEX(row, column)] == DEAD_CELL)
	{
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
	}
	else if (matrix[INDEX(row, column)] == LIVE_CELL)
	{
		SDL_SetRenderDrawColor(renderer, 115, 115, 115, 255);
	}
	SDL_RenderFillRect(renderer, &cell);
	SDL_RenderRect(renderer, &cell);
}

void RenderMatrix(SDL_Renderer* renderer, uint8_t* matrix)
{
	for (int row = 0; row < GRID_ROWS; ++row)
	{
		for (int col = 0; col < GRID_COLS; ++col)
		{
			displayMatrix(matrix, renderer, row, col);
		}
	}
}