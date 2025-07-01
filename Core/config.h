#pragma once

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define GRID_ROWS 100
#define GRID_COLS 75

#define DEAD_CELL 0
#define LIVE_CELL 1

#define PADDING 1.f

#define CELL_SIZE_X ((float)(WINDOW_WIDTH - (GRID_ROWS + 1) * PADDING) / (float)GRID_ROWS)
#define CELL_SIZE_Y ((float)(WINDOW_HEIGHT - (GRID_COLS + 1) * PADDING) / (float)GRID_COLS)

#define INDEX(r, c) ((r) * GRID_COLS + (c))