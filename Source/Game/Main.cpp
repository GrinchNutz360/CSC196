#include <SDL3/SDL.h>
#include <iostream>
#include "Core\Random.h"
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    //SDL_FRect greenSquare{ 270, 190, 200, 200 };
   

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

         // Set render draw color to green
       // SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle
        for (int i = 0; i < 100; ++i) {
            SDL_SetRenderDrawColor(renderer, viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), 255);
            SDL_RenderLine(renderer, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
            SDL_RenderPoint(renderer, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        }
        

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}