#include "sdl_wrapper.h"

#include <SDL.h>
#include <iostream>
#include <memory>

std::unique_ptr<SDL> sdl;

// TODO: pass in window width/height from config
bool start_sdl()
{
    std::cout << "Starting SDL" << std::endl;

    sdl = std::make_unique<SDL>();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    sdl->window = SDL_CreateWindow("SyndicusRL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);
    if (!sdl->window) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdl->renderer) {
        std::cout << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
        return false;
    }

    // game art is rendered in 640x360
    SDL_RenderSetLogicalSize(sdl->renderer, 640, 360);

    return true;
}

void end_sdl()
{
    std::cout << "Stopping SDL" << std::endl;

    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->window);
    sdl.reset();
    SDL_Quit();
}
