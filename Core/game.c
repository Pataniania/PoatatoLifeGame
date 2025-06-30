#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int SDLInitialization()
{

	if (SDL_Init(SDL_INIT_EVENTS) < 0)
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Life Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	renderer = SDL_CreateRenderer(window, NULL, 0);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

int GridInitialization(int matrix[][GRID_HEIGHT])
{
	for (int row = 0; row < GRID_WIDTH; row++)
	{
		for (int column = 0; column < GRID_HEIGHT; column++)
		{
			matrix[row][column] = DEAD_CELL;
		}
	}
	return 0;
}
void HandleQuitEvent(SDL_Event event, bool* done)
{
	if (event.type == SDL_EVENT_QUIT)
	{
		*done = true;
	}

}

void GridUpdate(int matrix[][GRID_HEIGHT])
{
	int(*previous)[GRID_HEIGHT] = malloc(sizeof(int) * GRID_WIDTH * GRID_HEIGHT);

	if (!previous)
	{
		printf("ERROR couldn't allocate memory\n");
		return;
	}

	// Copy current state
	for (int row = 0; row < GRID_WIDTH; ++row)
		for (int col = 0; col < GRID_HEIGHT; ++col)
			previous[row][col] = matrix[row][col];

	// Update matrix based on previous state
	for (int row = 0; row < GRID_WIDTH; row++)
	{
		for (int col = 0; col < GRID_HEIGHT; col++)
		{
			int liveNeighboursCount = CountLiveNeighbors(previous, row, col);
			// You should assign the returned cell state to matrix[row][col]
			matrix[row][col] = GetNextGridState(previous[row][col], liveNeighboursCount);
		}
	}

	free(previous);
}

int CountLiveNeighbors(int matrix[][GRID_HEIGHT], int row, int col)
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

bool IsAlive(int matrix[][GRID_HEIGHT], int row, int col)
{
	return row >= 0 && row < GRID_WIDTH && col >= 0 && col < GRID_HEIGHT && matrix[row][col] == LIVE_CELL;
}

void printMatrix(int matrix[GRID_HEIGHT][GRID_HEIGHT])
{
	/*ONLY FOR TEST PURPOSES IN THE GAME.C FILE*/
	printf("______________________________________________\n");

	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int column = 0; column < GRID_WIDTH; column++) {
			printf("%d ", matrix[row][column]);
		}
		printf("\n");
	}
}

void displayMatrix(int matrix[][GRID_HEIGHT], SDL_Renderer* renderer, int row, int column)
{
	SDL_FRect cell = { column * (CELL_SIZE_X + PADDING), row * (CELL_SIZE_Y + PADDING), CELL_SIZE_X, CELL_SIZE_Y };

	if (matrix[row][column] == DEAD_CELL)
	{
		SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255);
	}
	else if (matrix[row][column] == LIVE_CELL)
	{
		SDL_SetRenderDrawColor(renderer, 79, 115, 71, 255);
	}
	SDL_RenderFillRect(renderer, &cell);
	SDL_RenderRect(renderer, &cell);
}

void RenderMatrix(SDL_Renderer* renderer, int matrix[][GRID_HEIGHT])
{
	for (int row = 0; row < GRID_WIDTH; ++row)
	{
		for (int col = 0; col < GRID_HEIGHT; ++col)
		{
			displayMatrix(matrix, renderer, row, col);
		}
	}
}

void GetMousePosition(SDL_Event event, int matrix[][GRID_HEIGHT])
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


		if (cellRow >= 0 && cellRow < GRID_WIDTH &&
			cellCol >= 0 && cellCol < GRID_HEIGHT)
		{
			matrix[cellRow][cellCol] = !matrix[cellRow][cellCol];
		}
		/*printf("Raw mouse coordinates %f:%f \n", x, y);

		int cellRow = (x - PADDING) / (CELL_SIZE_X + PADDING);
		int cellCol = (y - PADDING) / (CELL_SIZE_Y + PADDING);

		printf("Grid coordinates %d:%d \n", cellRow, cellCol);

		}*/

	}
}

void HandleKeyPress(SDL_Event event, int matrix[][GRID_HEIGHT])
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_SPACE)
		{
			printf("\nSimulation started\n");
			GridUpdate(matrix);
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



//
//int placingCells(int** matrix) {
//	//just read ^^
//
//	SDL_Event event;
//
//	int xMouse;
//	int yMouse;
//
//	SDL_GetMouseState(&xMouse, &yMouse);
//
//	int rowGridY = yMouse / GRID_CELL_SIZE;
//	int rowGridX = xMouse / GRID_CELL_SIZE;
//
//
//
//	while (SDL_PollEvent(&event) > 0) {
//		switch (event.type) {
//
//		case SDL_EVENT_MOUSE_BUTTON_DOWN:
//			for (int row = 0; row < GRID_HEIGHT; row++) {
//				for (int column = 0; column < GRID_WIDTH; column++) {
//					matrix[rowGridY][rowGridX] = 1;
//
//					if (matrix[rowGridY][rowGridX] == 1) {
//						matrix[rowGridY][rowGridX] = 0;
//
//						printf("clicked on cel\n");
//					}
//				}
//			}
//
//
//			printMatrix(matrix);
//
//			break;
//		}
//	}
//	return 0;
//}
//
//int updateManager(int** matrix) {
//	//Toggle update
//	const Uint8* state = SDL_GetKeyboardState(NULL);
//
//	if (state[SDL_SCANCODE_SPACE] && !lastKeyState) {
//		keyToggled = !keyToggled;
//		printf("Key toggled %d\n", keyToggled);
//
//	}
//	if (keyToggled) {
//		updateMatrix(matrix);
//
//	}
//	lastKeyState = state[SDL_SCANCODE_SPACE];
//	//Update by frame
//	if (state[SDL_SCANCODE_U]) {
//		updateMatrix(matrix);
//	}
//	return 0;
//}

//void updateMatrix(int** matrix) {
//	checkForNeighbors(matrix);
//
//	generation += 1;
//	printf("Generation %d \n", generation);
//	printf("The matrix was updated ");
//
//}