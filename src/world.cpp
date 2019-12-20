#include "world.h"

#include "game.h"
#include "sdl_wrapper.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

void World::load_map( const std::string& file_name )
{
    std::ifstream map_file( file_name );
    if ( map_file.fail() ) {
        std::cout << "could not read from file " << file_name << std::endl;
        return;
    }

    tiles.clear();

    std::vector<std::string> lines;
    for ( std::string line; std::getline( map_file, line ); ) {
        lines.push_back( line );
    }

    tiles.resize( lines.size() );

    std::cout << "tile rows " << tiles.size() << std::endl;

    for ( int i = 0; i < lines.size(); i++ ) {
        auto& line = lines[i];
        parse_csv_line( line, tiles[i] );
    }

    map_file.close();
}

void World::render()
{
    int tile_size = 16;

    for ( int y = 0; y < tiles.size(); y++ ) {
        auto& row = tiles[y];
        for ( int x = 0; x < row.size(); x++ ) {
            std::string texture_name = determine_texture( row[x] );

            Texture* texture = game->assets->get_texture( texture_name );
            if ( !texture ) {
                continue;
            }

            SDL_Rect rect = {
                x * tile_size,
                y * tile_size,
                tile_size,
                tile_size};
            SDL_RenderCopy( sdl->renderer, texture->tex, NULL, &rect );
        }
    }
}

World::~World()
{
}

static std::string determine_texture( int id )
{
    switch ( id ) {
    case 0:
        return "data/gfx/wall.png";
    case 1:
        return "data/gfx/wall_top.png";
    case 2:
        return "data/gfx/floor.png";
    default:
        return "";
    }
}

static void parse_csv_line( const std::string& line, std::vector<int>& vec )
{
    std::stringstream ss( line );
    std::string token;
    while ( std::getline( ss, token, ',' ) ) {
        // convert from ASCII into integer
        int result;
        std::stringstream converter( token );
        converter >> result;
        vec.push_back( result );
    }
}
