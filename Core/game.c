#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

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

	font = TTF_OpenFont("Minecraft.ttf", 24);

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
		GridPosition mousePos = GetMouseCoordinatesInGrid();

		if (mousePos.row >= 0 && mousePos.row < GRID_ROWS &&
			mousePos.col >= 0 && mousePos.col < GRID_COLS)
		{
			matrix[INDEX(mousePos.row, mousePos.col)] = !matrix[INDEX(mousePos.row, mousePos.col)];
		}
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
bool IsWitinBound(int row, int col)
{

	if (col >= 0 && row < GRID_ROWS &&
		col >= 0 && col < GRID_COLS)
	{
		return true;
	}
	return false;
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
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y)
{
	SDL_Color color = { 255, 255, 255, 255 }; // White color

	// Create surface from the text
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, strlen(text), color);
	if (!surface) {
		SDL_Log("Failed to create text surface: %s", SDL_GetError());
		return;
	}

	// Create texture from surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log("Failed to create text texture: %s", SDL_GetError());
		SDL_DestroySurface(surface);
		return;
	}

	// Setup destination rectangle for rendering the text texture
	SDL_Rect dstRect = { x, y, surface->w, surface->h };

	// Free the surface, we don't need it anymore
	SDL_DestroySurface(surface);

	// Render the texture to the renderer
	if (SDL_RenderTexture(renderer, texture, NULL, &dstRect) != 0) {
		SDL_Log("Failed to render text texture: %s", SDL_GetError());
	}

	// Destroy the texture after rendering
	SDL_DestroyTexture(texture);
}
//For your own good don't read this
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
void CleanUp()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	TTF_CloseFont(font);
	font = NULL;
	TTF_Quit();
	SDL_Quit();
}
int GameLoop()
{
	bool done = false;
	bool toggleUpdate = false;

	uint8_t* matrix = malloc(sizeof(uint8_t) * GRID_ROWS * GRID_COLS);
	if (!matrix)
	{
		SDL_Log("Failed to allocate grid memory");
		return -1;
	}

	uint8_t* previous = malloc(sizeof(uint8_t) * GRID_ROWS * GRID_COLS);
	if (!previous)
	{
		SDL_Log("Failed to allocate grid memory");
		return -1;
	}

	if (!SDLInitialization())
	{
		return -1;
	}

	GridInitialization(matrix);

	while (!done)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			HandleQuitEvent(event, &done);
			GetMousePosition(event, matrix);
			HandleKeyPress(event, matrix, previous, &toggleUpdate);
		}
		if (toggleUpdate)
		{
			GridUpdate(matrix, previous);
			SDL_Delay(100);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		//RenderText(renderer,font, "salem", 10,10);
		RenderMatrix(renderer, matrix);

		SDL_RenderPresent(renderer);

	}
	free(matrix);
	free(previous);
	CleanUp();
	
}


