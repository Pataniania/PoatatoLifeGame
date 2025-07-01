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


