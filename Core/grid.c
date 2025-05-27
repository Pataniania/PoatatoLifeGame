#include <stdio.h>
#include <SDL3/SDL.h>

#include "constants.h"
#include "grid.h"

SDL_Event event;
bool mouse_active = false;
bool mouse_hover = false;

SDL_Color grid_background = { 255, 182, 193, 255 }; // Light Pink
SDL_Color grid_line_color = { 255, 192, 203, 255 }; // Pink
SDL_Color grid_cursor_ghost_color = { 255, 192, 203, 255 }; // Pink
SDL_Color grid_cursor_color = { 255, 255, 255, 255 }; // White

SDL_Rect grid_cursor = {
		.x = (GRID_HEIGHT - 1) / 2 * GRID_CELL_SIZE,
		.y = (GRID_HEIGHT - 1) / 2 * GRID_CELL_SIZE,
		.w = GRID_CELL_SIZE,
		.h = GRID_CELL_SIZE,
};

int cursor_position() {
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		switch (event.type) {
		case SDLK_Z:
			grid_cursor.y -= GRID_CELL_SIZE;
			break;
		case SDLK_S:
			grid_cursor.y += GRID_CELL_SIZE;
			break;
		case SDLK_Q:
			grid_cursor.x -= GRID_CELL_SIZE;
			break;
		case SDLK_D:
			grid_cursor.x += GRID_CELL_SIZE;
			break;
		}
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		grid_cursor.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
		grid_cursor.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
		break;
		//case SDL_EVENT_WINDOW:
		//	if (event.window.event == SDL_EVENT_WINDOW_MOUSE_ENTER && !mouse_hover)
		//		mouse_hover = true;
		//	else if (event.window.event == SDL_EVENT_WINDOW_MOUSE_LEAVE
		//		&& mouse_hover)
		//		mouse_hover = false;
		//	break;
	}
}

void RenderDrawGrid(SDL_Renderer* renderer)
{
	for (int x = 0; x < GRID_WIDTH; x += GRID_CELL_SIZE)
	{
		for (int y = 0; y < GRID_HEIGHT; y += GRID_CELL_SIZE)
		{

			SDL_FRect rect = { x, y, GRID_CELL_SIZE, GRID_CELL_SIZE };
			SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

int draw_grid(SDL_Renderer* renderer) {
	/*Draw grid background.*/
	SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
		grid_background.b, grid_background.a);
	SDL_RenderClear(renderer);

	// Draw grid lines.
	SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
		grid_line_color.b, grid_line_color.a);

	for (int x = 0; x < 1 + GRID_WIDTH * GRID_CELL_SIZE;
		x += GRID_CELL_SIZE) {
		SDL_RenderLine(renderer, x, 0, x, WINDOW_HEIGHT);
	}
	for (int y = 0; y < 1 + GRID_HEIGHT * GRID_CELL_SIZE;
		y += GRID_CELL_SIZE) {
		SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
	}
	return 0;
}

int draw_cursor(SDL_Renderer* renderer) {
	// Draw grid cursor.
	SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
		grid_cursor_color.g, grid_cursor_color.b,
		grid_cursor_color.a);
	SDL_RenderFillRect(renderer, &grid_cursor);
	return 0;
}