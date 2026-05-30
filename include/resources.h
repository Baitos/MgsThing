#pragma once

#include <vector>
#include <string>

#include "../ext/glm/glm.hpp"
#include "animation.h"

struct SDLState; // forward def
struct SDL_Texture;

struct Resources { 
    std::vector<SDL_Texture *> textures;

    SDL_Texture *tileSet;
    int tileSetCols; // amount of columns in tileSet

    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &filepath);
    void load(SDLState &state);
    void unload();

    Resources(){};
};