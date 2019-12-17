#include "assets.h"

#include <SDL_image.h>
#include <iostream>
#include <unordered_map>

using namespace std;

void Assets::load_texture( SDL_Renderer *renderer, const string &file_name )
{
    auto sdl_texture = IMG_LoadTexture( renderer, file_name.c_str() );
    if ( !sdl_texture ) {
        cout << "texture " << file_name << " was not found" << endl;
        return;
    }

    TexturePtr texture = unique_ptr<Texture, TextureDestroyer>( new Texture() );
    texture->tex = sdl_texture;
    SDL_QueryTexture( texture->tex, NULL, NULL, &texture->rect.w, &texture->rect.w );
    texture_map.insert( make_pair( file_name, move( texture ) ) );
}

Texture *Assets::get_texture( const string &file_name )
{
    auto texture = texture_map.find( file_name );
    if ( texture == texture_map.end() ) {
        return nullptr;
    }
    return texture->second.get();
}

Assets::~Assets()
{
}
