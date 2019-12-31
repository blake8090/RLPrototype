#include "assets.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>

using namespace std;

void Assets::load_texture(SDL_Renderer* renderer, const string& file_name)
{
    auto sdl_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!sdl_texture) {
        cout << "texture " << file_name << " was not found" << endl;
        return;
    }

    TexturePtr texture = unique_ptr<Texture, TextureDestroyer>(new Texture());
    texture->tex = sdl_texture;
    // TODO: really only need width and height on texture, not full SDL_Rect
    SDL_QueryTexture(texture->tex, NULL, NULL, &texture->rect.w, &texture->rect.h);
    texture_map.insert(make_pair(file_name, move(texture)));
    cout << "Successfully loaded texture " << file_name << endl;
}

Texture* Assets::get_texture(const string& file_name)
{
    auto texture = texture_map.find(file_name);
    if (texture == texture_map.end()) {
        return nullptr;
    }
    return texture->second.get();
}

void Assets::load_tile_set(const std::string& file_name)
{
    tile_set = std::unique_ptr<TileSet>(new TileSet());
    tile_set->load_tile_set(file_name);
}

// TODO: maybe return a reference and assert that the tile set was loaded first?
TileSet* Assets::get_tile_set()
{
    return tile_set.get();
}
