#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool SDLInitialization()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVENTS) == false)
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	window = SDL_CreateWindow("Life Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		success = false;
	}
	renderer = SDL_CreateRenderer(window, NULL, 0);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		success = false;
	}

	if (TTF_Init() == false)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
	}
	TTF_Font* font = TTF_OpenFont("Minecraft.ttf", 24);

	if (!font)
	{
		SDL_Log("Failed to load font: %s", SDL_GetError());
	}
	return success;
}

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
void HandleQuitEvent(SDL_Event event, bool* done)
{
	if (event.type == SDL_EVENT_QUIT)
	{
		*done = true;
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
bool IsAlive(uint8_t* matrix, int row, int col)
{
	return row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS && matrix[INDEX(row, col)] == LIVE_CELL;
}
void printMatrix(uint8_t* matrix)
{
	/*ONLY FOR TEST PURPOSES IN THE GAME.C FILE*/
	printf("______________________________________________\n");

	for (int row = 0; row < GRID_COLS; row++) {
		for (int column = 0; column < GRID_ROWS; column++) {
			printf("%d ", matrix[INDEX(row, column)]);
		}
		printf("\n");
	}
}
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
void GetMousePosition(SDL_Event event, uint8_t* matrix)
{

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{

		float mouseX = -1;
		float mouseY = -1;

		SDL_GetMouseState(&mouseX, &mouseY);

		printf("Raw mouse coordinates %f:%f \n", mouseX, mouseY);

		int cellRow = (int)(mouseY / (CELL_SIZE_Y + PADDING));
		int cellCol = (int)(mouseX / (CELL_SIZE_X + PADDING));

		printf("Grid coordinates %d:%d \n", cellRow, cellCol);


		if (cellRow >= 0 && cellRow < GRID_ROWS &&
			cellCol >= 0 && cellCol < GRID_COLS)
		{
			matrix[INDEX(cellRow, cellCol)] = !matrix[INDEX(cellRow, cellCol)];
		}
		/*printf("Raw mouse coordinates %f:%f \n", x, y);

		int cellRow = (x - PADDING) / (CELL_SIZE_X + PADDING);
		int cellCol = (y - PADDING) / (CELL_SIZE_Y + PADDING);

		printf("Grid coordinates %d:%d \n", cellRow, cellCol);

		}*/

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

	}
}
int GetNextGridState(int currentCell, int liveNeighbours)
{
	if (currentCell == LIVE_CELL)
	{
		return (liveNeighbours < 2 || liveNeighbours > 3) ? DEAD_CELL : LIVE_CELL;
	}
	else // currentCell == DEAD_CELL
	{
		return (liveNeighbours == 3) ? LIVE_CELL : DEAD_CELL;
	}
}


