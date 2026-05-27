
#include <SDL3_image/SDL_image.h>
#include "../include/resources.h"
#include "../include/state.h"

SDL_Texture* Resources::loadTexture(SDL_Renderer *renderer, const std::string &filepath) { // load texture from filepath
    // load game assets
    SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.c_str());
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST); // pixel perfect
    textures.push_back(tex);
    return tex;
}

void Resources::load(SDLState &state) { // First variable controls how many frames there are, second is how long each frame lasts (in seconds)
    this->texPlayer = loadTexture(state.renderer, "data/logo.png");
}

void Resources::unload() {
    for (SDL_Texture *tex : textures) {
        SDL_DestroyTexture(tex);
    }
}