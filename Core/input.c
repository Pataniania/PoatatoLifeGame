#include "input.h"

void HandleQuitEvent(SDL_Event event, bool* done)
{
	if (event.type == SDL_EVENT_QUIT)
	{
		*done = true;
	}

}
GridPosition GetMouseCoordinatesInGrid()
{
	int** coordinates = 0;
	float mouseX = -1;
	float mouseY = -1;

	GridPosition pos;

	SDL_GetMouseState(&mouseX, &mouseY);

	pos.row = (int)(mouseY / (CELL_SIZE_Y + PADDING));
	pos.col = (int)(mouseX / (CELL_SIZE_X + PADDING));

	return pos;
}
void GetMousePosition(SDL_Event event, uint8_t* matrix)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		GridPosition mousePos = GetMouseCoordinatesInGrid();

		if (mousePos.row >= 0 && mousePos.row < GRID_ROWS &&
			mousePos.col >= 0 && mousePos.col < GRID_COLS)
		{
			matrix[INDEX(mousePos.row, mousePos.col)] = !matrix[INDEX(mousePos.row, mousePos.col)];
		}
	}
}
void HandleKeyPress(SDL_Event event, uint8_t* matrix, uint8_t* previous, bool* toggleUpdate)
{

	if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
	{
		if (event.key.key == SDLK_U)
		{
			GridUpdate(matrix, previous);
		}

		if (event.key.key == SDLK_R)
		{
			for (int i = 0; i < 30; i++)
			{
				matrix[INDEX(rand() % GRID_COLS + 1, rand() % GRID_ROWS + 1)] = LIVE_CELL;
			}
		}
		if (event.key.key == SDLK_C)
		{
			GridInitialization(matrix);
		}

		if (event.key.key == SDLK_SPACE)
		{
			*toggleUpdate = !(*toggleUpdate);
		}
		if (event.key.key == SDLK_A)
		{
			PlacePatternPentomino(matrix);
		}
		if (event.key.key == SDLK_Z)
		{
			PlacePatternRings(matrix);
		}
		if (event.key.key == SDLK_E)
		{
			PlacePatternReflector(matrix);
		}
	}
}
void PlacePatternPentomino(uint8_t* matrix)
{
	GridPosition mousePos = GetMouseCoordinatesInGrid();
	if (IsWitinBound(mousePos.row, mousePos.col))
	{
		matrix[INDEX(mousePos.row, mousePos.col)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col + 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col - 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col + 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col)] = LIVE_CELL;
	}
}
void PlacePatternRings(uint8_t* matrix)
{
	GridPosition mousePos = GetMouseCoordinatesInGrid();
	if (IsWitinBound(mousePos.row, mousePos.col))
	{
		matrix[INDEX(mousePos.row, mousePos.col + 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col + 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col + 1)] = LIVE_CELL;

		matrix[INDEX(mousePos.row + 1, mousePos.col + 2)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col + 2)] = LIVE_CELL;

		matrix[INDEX(mousePos.row, mousePos.col + 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col + 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col + 3)] = LIVE_CELL;

		matrix[INDEX(mousePos.row, mousePos.col - 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col - 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col - 1)] = LIVE_CELL;

		matrix[INDEX(mousePos.row + 1, mousePos.col - 2)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col - 2)] = LIVE_CELL;

		matrix[INDEX(mousePos.row, mousePos.col - 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col - 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col - 3)] = LIVE_CELL;
	}
}
void PlacePatternReflector(uint8_t* matrix)
{
	GridPosition mousePos = GetMouseCoordinatesInGrid();
	if (IsWitinBound(mousePos.row, mousePos.col))
	{
		matrix[INDEX(mousePos.row, mousePos.col)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col + 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col + 2)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col + 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col + 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col + 4)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col + 5)] = LIVE_CELL;

		matrix[INDEX(mousePos.row, mousePos.col - 1)] = LIVE_CELL;
		matrix[INDEX(mousePos.row + 1, mousePos.col - 2)] = LIVE_CELL;
		matrix[INDEX(mousePos.row - 1, mousePos.col - 2)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col - 3)] = LIVE_CELL;
		matrix[INDEX(mousePos.row, mousePos.col - 4)] = LIVE_CELL;
	}
}

bool IsWitinBound(int row, int col)
{

	if (col >= 0 && row < GRID_ROWS &&
		col >= 0 && col < GRID_COLS)
	{
		return true;
	}
	return false;
}