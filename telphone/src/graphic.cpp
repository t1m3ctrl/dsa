#include "../include/graphic.h"
#include <algorithm>

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{650};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void WindowOutput(int** a, int alg_num, int n_count)
{
    init();
    bool run = true;
    SDL_Event event;

    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;
        }
        DrawOs();
        DrawGraphics(a, alg_num, n_count);
        SDL_RenderPresent(renderer);

        SDL_Delay(200);
    }
    quit();
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL couldn't initialize: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
            "Algorithms graph m(f)+c(f)",
            50,
            50,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        printf("SDL couldn't create window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL couldn't create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void quit()
{
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_Quit();
}

void DrawOs()
{
    // SDL_Rect rect_red = {200, 575, 25, 25};
    // SDL_Rect rect_blue = {400, 575, 25, 25};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    // SDL_RenderFillRect(renderer, &rect_blue);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    // SDL_RenderFillRect(renderer, &rect_red);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    // SDL_RenderDrawRect(renderer, &rect_blue);
    // SDL_RenderDrawRect(renderer, &rect_red);
    // Ox
    SDL_RenderDrawLine(renderer, 50, 550, 750, 550);
    // Oy
    SDL_RenderDrawLine(renderer, 50, 550, 50, 50);

    // Arrows
    SDL_RenderDrawLine(renderer, 50, 50, 53, 55);
    SDL_RenderDrawLine(renderer, 50, 50, 47, 55);

    SDL_RenderDrawLine(renderer, 750, 550, 745, 553);
    SDL_RenderDrawLine(renderer, 750, 550, 745, 547);
}

void DrawGraphics(int** a, int alg_num, int n_count)
{
    int max_c = a[0][0];
    int i, j;

    for (i = 0; i < alg_num; i++) {
        for (j = 0; j < n_count; j++) {
            if (a[i][j] > max_c)
                max_c = a[i][j];
        }
    }                               // to convert our value
    double k = (1.0 * max_c / 500); // into SDL coordinates
    double kx = (1.0 * 700 / n_count);

    for (i = 0; i < alg_num; i++) {
        int n = 50 + kx; // SDL 50 y (Our values must be between 50 and 750)
        if (i == 0)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // RED
        if (i == 1)
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0); // AQUA
        if (i == 2)
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0); // FUCHSIA
        if (i == 3)
            SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0); // GREEN
        if (i == 4)
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); // YELLOW
        if (i == 5)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // BLUE
        if (i == 6)
            SDL_SetRenderDrawColor(renderer, 128, 128, 0, 0); // OLIVE
        if (i == 7)
            SDL_SetRenderDrawColor(renderer, 192, 192, 192, 0); // SILVER

        for (j = 0; j < n_count - 1; j++) {
            SDL_RenderDrawLine(
                    renderer,
                    n,
                    550 - ((0.0 + a[i][j]) / k),
                    n + kx,
                    550 - ((0.0 + a[i][j + 1]) / k));
            n += kx;
        }
    }
}