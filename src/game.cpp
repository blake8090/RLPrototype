#include "game.h"

#include "sdl_wrapper.h"

#include <iostream>

bool Game::start_up()
{
    std::cout << "Starting up engine" << std::endl;

    if ( !start_sdl() ) {
        return false;
    }

    // assets->load_texture( sdl->renderer, "test3.png" );
    // if ( assets->get_texture( "test3.png" ) ) {
    //     std::cout << "wow the texture is here" << std::endl;
    // }

    running = true;

    return true;
}

void Game::shut_down()
{
    std::cout << "Shutting down engine" << std::endl;
    end_sdl();
}

bool Game::is_running()
{
    return running;
}

void Game::update()
{
    SDL_Event e;
    if ( SDL_PollEvent( &e ) ) {
        if ( e.type == SDL_QUIT ) {
            running = false;
        } else if ( e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE ) {
            running = false;
        }
    }

    SDL_RenderClear( sdl->renderer );
    // SDL_RenderCopy( sdl->renderer, img, NULL, &texr );
    SDL_RenderPresent( sdl->renderer );
}

Game::~Game()
{
}
