#include "../include/graphic.h"
#include <algorithm>

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{650};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool run = true;
SDL_Event event;

void WindowOutput2(int* a, int* b)
{
    init();
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;
        }
        DrawOs();
        DrawGraphics2(a, b);
        SDL_RenderPresent(renderer);

        SDL_Delay(200);
    }
    quit();
}

void WindowOutput4(int* a, int* b, int* c, int* d)
{
    init();
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;
        }
        DrawOs();
        DrawGraphics4(a, b, c, d);
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

void DrawGraphics2(int* a, int* b)
{
    int max_c;
    if (a[4] > b[4])
        max_c = a[4];
    else
        max_c = b[4];        // to convert our value
    float k = (max_c / 700); // into SDL coordinates
    int n = 500 - 50;        // SDL 50 y (Our values must be between 50 and 550)

    for (int i = 0; i < 4; i++) {
        // for a
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawLine(
                renderer, (a[i] / k) + 50, n, (a[i + 1] / k) + 50, n - 100);
        // for b
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        SDL_RenderDrawLine(
                renderer, (b[i] / k) + 50, n, (b[i + 1] / k) + 50, n - 100);

        n -= 100;
    }
}

void DrawGraphics4(int* a, int* b, int* c, int* d)
{
    int max_c;
    if (a[4] > b[4])
        max_c = a[4];
    else
        max_c = b[4];
    if (c[4] > max_c)
        max_c = c[4];
    if (d[4] > max_c)
        max_c = d[4];        // to convert our value
    float k = (max_c / 700); // into SDL coordinates
    int n = 500 - 50;        // SDL 50 y (Our values must be between 50 and 550)

    for (int i = 0; i < 4; i++) {
        // for a
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawLine(
                renderer, (a[i] / k) + 50, n, (a[i + 1] / k) + 50, n - 100);
        // for b
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderDrawLine(
                renderer, (b[i] / k) + 50, n, (b[i + 1] / k) + 50, n - 100);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        SDL_RenderDrawLine(
                renderer, (c[i] / k) + 50, n, (c[i + 1] / k) + 50, n - 100);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderDrawLine(
                renderer, (d[i] / k) + 50, n, (d[i + 1] / k) + 50, n - 100);

        n -= 100;
    }
}