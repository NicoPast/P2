#include "SDL.h";
#include "SDL_ttf.h";
#include "SDL_image.h";

#include "checkML.h";
#include <stdio.h>;
#include <string>;
#include <iostream>
 /*
int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);


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
    std::string file = "../assets/fonts/OpenSans-Bold.ttf";
    TTF_Font* font = TTF_OpenFont(file.c_str(),72);
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Prueba TTF", { 255,255,255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Surface* imgSurface = IMG_Load("../assets/example.png");
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);

    SDL_SetRenderDrawColor(renderer, 124, 255, 255, 124);

    SDL_Rect rectangle;
    int x = 320;
    int y = 240;
    int w = 250;
    int h = 50;
    rectangle.x = x-(w/2);
    rectangle.y = y-(h/2);
    rectangle.w = w;
    rectangle.h = h;

    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderCopy(renderer, texture, NULL, &rectangle);


    rectangle.w = 200;
    rectangle.h = 200;
    rectangle.y -= 200;
    rectangle.x += 25;

    SDL_RenderCopy(renderer, imgTexture, NULL, &rectangle);


    SDL_RenderPresent(renderer);
    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);


    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    TTF_Quit();
    return 0;
}
*/