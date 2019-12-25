#include "tile_set.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void TileSet::load_tile_set( const std::string& file_name )
{
    std::ifstream jsonFile( file_name );
    if ( jsonFile.fail() ) {
        std::cout << "could not read from file " << file_name << std::endl;
        return;
    }

    json j;
    jsonFile >> j;

    try {
        for ( auto& node : j ) {
            Tile* t = new Tile();

            // tiles need an image, so let this blow up if it's missing
            t->gfx = node["gfx"];

            if ( node.contains( "ceilingGfx" ) ) {
                t->ceilingGfx = node["ceilingGfx"];
            }

            if ( node.contains( "collidable" ) ) {
                t->collidable = node["collidable"];
            }

            tiles.push_back( std::unique_ptr<Tile>( t ) );
        }
        std::cout << "TileSet: Loaded " << tiles.size() << " tiles." << std::endl;
    } catch ( nlohmann::detail::type_error& e ) {
        // TODO: Better handling
        std::cout << e.what() << std::endl;
        return;
    }
}

Tile* TileSet::get_tile( int id )
{
    if ( id < 0 || id >= tiles.size() ) {
        return nullptr;
    }
    // TODO: Check if tile actually exists
    return tiles[id].get();
}

TileSet::~TileSet()
{
}
