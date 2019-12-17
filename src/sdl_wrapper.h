#pragma once

#include <memory>
#include <SDL.h>

struct SDL {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

bool start_sdl();
void end_sdl();

extern std::unique_ptr<SDL> sdl;
