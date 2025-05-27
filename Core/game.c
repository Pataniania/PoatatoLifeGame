#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int SDLInitialization()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer("Life Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_FOCUS, &window, &renderer);

	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

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
			matrix[row][column] = 0;

		}
	}
}
void HandleQuitEvent(SDL_Event event, bool done)
{
	if (event.type == SDL_EVENT_QUIT)
	{
		done = true;
	}

}

void GridUpdate(int matrix[][GRID_HEIGHT])
{
	for (int row = 0; row < GRID_WIDTH; row++)
	{
		for (int column = 0; column < GRID_HEIGHT; column++)
		{
			int liveNeighboursCount = CountLiveNeighbors(gameArr, row, column);
			GetNextGridState(matrix, liveNeighboursCount, row, column);
		}
	}
}

int CountLiveNeighbors(int matrix[][GRID_HEIGHT], int row, int col)
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
				return liveNeighborCount++;
			}
		}
	}
}

bool IsAlive(int matrix[][GRID_HEIGHT], int row, int col)
{
	return
		row >= 0 && row < GRID_HEIGHT && col >= 0 && col < GRID_WIDTH
		&&
		matrix[row][col] == 1;
}

int AllocateMatrix()
{
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
}

//
void printMatrix(int matrix[][GRID_HEIGHT])
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