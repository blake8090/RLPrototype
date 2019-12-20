#pragma once

#include <SDL.h>
#include <memory>

struct SDL {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

bool start_sdl();
void end_sdl();

extern std::unique_ptr<SDL> sdl;
