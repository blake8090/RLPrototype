#define SDL_MAIN_HANDLED

#include "game.h"

#include <SDL.h>
#include <iostream>

std::unique_ptr<Game> game;

int main()
{
    game = std::make_unique<Game>();
    if ( !game->start_up() ) {
        return EXIT_FAILURE;
    }

    while ( game->is_running() ) {
        game->update();
    }

    game->shut_down();

    return 0;
}
