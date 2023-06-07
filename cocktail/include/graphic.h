#pragma once
#include <SDL2/SDL.h>

#define COLOR_1 RED
#define COLOR_2 AQUA
#define COLOR_3 FUCHSIA
#define COLOR_4 GREEN
#define COLOR_5 YELLOW
#define COLOR_6 BLUE
#define COLOR_7 OLIVE
#define COLOR_8 SILVER

void init();
void quit();
void DrawOs();
void DrawGraphics(int** a, int alg_num);
void WindowOutput(int** a, int alg_num);
