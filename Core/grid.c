#include "grid.h"

void GridInitialization(uint8_t* matrix)
{

	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int column = 0; column < GRID_COLS; column++)
		{
			matrix[INDEX(row, column)] = DEAD_CELL;
		}
	}
}
void GridUpdate(uint8_t* matrix, uint8_t* previous)
{
	if (!previous)
	{
		printf("ERROR couldn't allocate memory\n");
		return;
	}

	// Copy current state
	for (int row = 0; row < GRID_ROWS; ++row)
		for (int col = 0; col < GRID_COLS; ++col)
			previous[INDEX(row, col)] = matrix[INDEX(row, col)];

	// Update matrix based on previous state
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int col = 0; col < GRID_COLS; col++)
		{
			int liveNeighboursCount = CountLiveNeighbors(previous, row, col);
			// You should assign the returned cell state to matrix[row][col]
			matrix[INDEX(row, col)] = GetNextGridState(previous[INDEX(row, col)], liveNeighboursCount);
		}
	}
}

int CountLiveNeighbors(uint8_t* matrix, int row, int col)
{
	int liveNeighborCount = 0;

	for (int dr = -1; dr <= 1; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (dr == 0 && dc == 0)
				continue;

			int r = row + dr;
			int c = col + dc;

			if (IsAlive(matrix, r, c))
				liveNeighborCount++;
		}
	}
	return liveNeighborCount;
}

int GetNextGridState(int currentCell, int liveNeighbours)
{
	if (currentCell == LIVE_CELL)
	{
		return (liveNeighbours < 2 || liveNeighbours > 3) ? DEAD_CELL : LIVE_CELL;
	}
	else
	{
		return (liveNeighbours == 3) ? LIVE_CELL : DEAD_CELL;
	}
}

bool IsAlive(uint8_t* matrix, int row, int col)
{
	return row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS && matrix[INDEX(row, col)] == LIVE_CELL;
}



