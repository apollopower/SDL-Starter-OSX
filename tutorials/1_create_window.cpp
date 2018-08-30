#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main()
{
    // SDL Didn't work
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Worked! Moving on and creating window

    SDL_Window *window; // Creating pointer for window struct

    window = SDL_CreateWindow(
        "Hello World!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,0);

    // Checking if window opened
    if (window == NULL) {
        cout << "Error initializing window: " << SDL_GetError() << endl;
        // Cleanup
        SDL_Quit();
        return 1;
    }

    // The window should now be open. Do magic programming here

    // ....

    SDL_Delay(5000); // Pause execution for 5 seconds

    // Close and destroy the window:
    SDL_DestroyWindow(window);

    // Cleanup
    SDL_Quit();
    return 0;
}