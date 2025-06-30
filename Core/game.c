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

int GridInitialization(int matrix[][GRID_WIDTH])
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

void GridUpdate(int matrix[][GRID_WIDTH])
{
	int previous[GRID_WIDTH][GRID_HEIGHT];

	for (int row = 0; row < GRID_WIDTH; ++row)
		for (int col = 0; col < GRID_HEIGHT; ++col)
			previous[row][col] = matrix[row][col];
		

	for (int row = 0; row < GRID_WIDTH; row++)
	{
		for (int column = 0; column < GRID_HEIGHT; column++)
		{
			int liveNeighboursCount = CountLiveNeighbors(previous, row, column);
			matrix = GetNextGridState(previous[row][column], liveNeighboursCount, row, column);;
		}
	}
}

int CountLiveNeighbors(int matrix[][GRID_WIDTH], int row, int col)
{
	int liveNeighborCount = 0;

	for (int neighborOffsetRow = -1; neighborOffsetRow <= 1; neighborOffsetRow++)
	{
		for (int neighborOffsetCol = -1; neighborOffsetCol <= 1; neighborOffsetCol++)
		{
			if (neighborOffsetRow == 0 && neighborOffsetCol == 0) continue;

			int neighborRow = row + neighborOffsetRow;
			int neighborCol = col + neighborOffsetCol;

			if (IsAlive(matrix, neighborRow, neighborCol))
			{
				liveNeighborCount++;
			}
		}
	}
	return;
}

bool IsAlive(int matrix[][GRID_WIDTH], int row, int col)
{
	return
		row >= 0 && row < GRID_HEIGHT && col >= 0 && col < GRID_WIDTH
		&&
		matrix[row][col] == 1;
}

void printMatrix(int matrix[GRID_HEIGHT][GRID_WIDTH])
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

void displayMatrix(int matrix[][GRID_WIDTH], SDL_Renderer* renderer, int row, int column)
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

void RenderMatrix(SDL_Renderer* renderer, int matrix[][GRID_WIDTH])
{
	for (int row = 0; row < GRID_HEIGHT; ++row)
	{
		for (int column = 0; column < GRID_WIDTH; ++column)
		{
			displayMatrix(matrix, renderer, row, column);
		}
	}
}

void GetMousePosition(SDL_Event event, int matrix[][GRID_WIDTH])
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


		if (cellCol >= 0 && cellCol < GRID_HEIGHT &&
			cellRow >= 0 && cellRow < GRID_WIDTH)
		{
			matrix[cellRow][cellCol] = !matrix[cellRow][cellCol];

			
			printf("Cell placed or removed");
		}
		printMatrix(matrix);


		/*printf("Raw mouse coordinates %f:%f \n", x, y);

		int cellRow = (x - PADDING) / (CELL_SIZE_X + PADDING);
		int cellCol = (y - PADDING) / (CELL_SIZE_Y + PADDING);

		printf("Grid coordinates %d:%d \n", cellRow, cellCol);

		}*/

	}
}

void HandleKeyPress(SDL_Event event, int matrix[][GRID_WIDTH])
{
	if (event.type == SDL_EVENT_KEY_DOWN) 
	{
		if (event.key.key == SDLK_SPACE) 
		{
			printf("\nSimulation started");
			GridUpdate(matrix);
			// handle spacebar
		}
	}

}




int GetNextGridState(int matrix[][GRID_HEIGHT], int liveNeighbours, int row, int col)
{

	if (matrix[row][col] == LIVE_CELL)
	{
		matrix[row][col] = liveNeighbours < 2 || liveNeighbours > 3 ? DEAD_CELL : LIVE_CELL;
	}

	if (matrix[row][col] == DEAD_CELL)
	{
		matrix[row][col] = liveNeighbours == 3 ? LIVE_CELL : DEAD_CELL;
	}
	return 0;
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