// Animation - Animates hello.jpg scrolling up the window

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

using namespace std;

// Setting up Constants:
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPEED = 300;

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

    // get AND SCALE DOWN the dimensions of the texture:
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;

    // Start sprite in the center of the screen, with
    // no velocity:
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    // Keep track of inputs that are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    // Set to 1 when "Close Window" button is pressed:
    bool close_requested = false;

    // Animation loop
    while (!close_requested)
    {
        // Process Events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                close_requested = true;
            }
        }

        // **MOUSE**

        // Get cursor position relative to window:
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x,&mouse_y);

        // Determine velocity toward mouse:
        int target_x = mouse_x - dest.w / 2;
        int target_y = mouse_y - dest.h / 2;
        float delta_x = target_x - x_pos;
        float delta_y = target_y - y_pos;
        // Pythagorean Thereom to calculate distance:
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

        // Prevent Jitter
        if (distance < 5) {
            x_vel = y_vel = 0;
        }
        else {
            x_vel = delta_x * SPEED / distance;
            y_vel = delta_y * SPEED / distance;
        }

        // Reverse velocity if mouse button 1 pressed
        // (bitwise AND)
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            x_vel = -x_vel;
            y_vel = -y_vel;
        }

        // Update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // Collision Detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

        // Set the positions in the struct
        dest.x = (int) x_pos;
        dest.y = (int) y_pos;

        // Clear the window
        SDL_RenderClear(rend);

        // Draw the image to the window:
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

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