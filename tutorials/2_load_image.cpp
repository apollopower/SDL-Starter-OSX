#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main()
{
    // Initial SDL Check
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Worked! Moving on and creating window
    SDL_Window* window;

    window = SDL_CreateWindow(
        "Hello World!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,0);

    // Window error check
    if (!window) {
        cout << "Error initializing window: " << SDL_GetError() << endl;
        // Cleanup
        SDL_Quit();
        return 1;
    }


    // **RENDERER**

    // Create a renderer, which sets up the graphics hardware:
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);

    // Checking if Renderer didn't work
    if (!rend) {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        // Cleanup
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load("resources/hello.jpg");

    if (!surface) {
        cout << "Error Creating surface\n";
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the image data into the graphics memory hardware, and freeing
    // surface from memory:
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    if (!tex) {
        cout << "Error creating texture: " << SDL_GetError() << endl;
        // Cleanup
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Clear the window:
    SDL_RenderClear(rend);

    // Draw the image to the window
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);


    cout << "Success!\n";

    SDL_Delay(5000); // Pause execution for 5 seconds

    // Cleanup of resources
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}