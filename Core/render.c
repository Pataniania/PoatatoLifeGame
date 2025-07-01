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