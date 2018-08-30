// Animation - Animates hello.jpg scrolling up the window

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

using namespace std;

// Setting up Constants:
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
// Speed in pixels per second
const int SCROLL_SPEED = 300;

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


    // **ANIMATION**

    // struct to hold the position and size of the sprite, declared
    // as a SDL rectangle:
    SDL_Rect dest;

    // get the dimensions of the texture:
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // position the sprite at the bottom of the window
    // origin is the top left corner, positive y is down
    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    // Require float resolution for y position
    float y_pos = WINDOW_HEIGHT;

    // Animation loop
    while (dest.y >= -dest.h)
    {
        // Clear the window
        SDL_RenderClear(rend);

        // Set the y position in the struct
        dest.y = (int) y_pos;

        // Draw the image to the window:
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

        // Update sprite position:
        y_pos -= (float) SCROLL_SPEED / 60;

        // Wait 1/60th of a second
        SDL_Delay(1000/60);
    }

    // Cleanup of resources
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();

    cout << "Success!\n";

    return 0;
}