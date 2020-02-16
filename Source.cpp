#include "SDL.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Carlos mira como configuramos nuestro proyecto!",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 124, 124, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 124, 255, 255, 124);

    SDL_Rect rectangle;
    int x = 320;
    int y = 240;
    int w = 50;
    int h = 50;

    rectangle.x = x-(w/2);
    rectangle.y = y-(h/2);
    rectangle.w = w;
    rectangle.h = h;


    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderPresent(renderer);
    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}