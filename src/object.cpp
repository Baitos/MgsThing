#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"

void Object::draw(const SDLState &state, GameState &gs) {
    SDL_FRect dst {
        .x = this->pos.x - gs.mapViewport.x,
        .y = this->pos.y - gs.mapViewport.y,
        .w = this->width,
        .h = this->height
    };
    SDL_RenderTexture(state.renderer, this->texture, nullptr, &dst);
    this->drawDebug(state, gs);
}

void Object::drawDebug(const SDLState &state, GameState &gs) {
    if (gs.debugMode && this->debug) {
        SDL_FRect rectA {
            .x = this->pos.x + this->collider.x - gs.mapViewport.x, 
            .y = this->pos.y + this->collider.y - gs.mapViewport.y,
            .w = this->collider.w, 
            .h = this->collider.h
        };
        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 150);
        SDL_RenderFillRect(state.renderer, &rectA);
        SDL_FRect sensor{  
            .x = this->pos.x + this->collider.x - gs.mapViewport.x,
            .y = this->pos.y + this->collider.y + this->collider.h - gs.mapViewport.y,
            .w = this->collider.w, 
            .h = 1
        };
        SDL_SetRenderDrawColor(state.renderer, 0, 0, 255, 150);
        SDL_RenderFillRect(state.renderer, &sensor);

        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_NONE);
    }
}

Object createObject(SDL_Texture *tex) {
   Object o;
   o.pos = glm::vec2(TILE_SIZE * 3, TILE_SIZE * 3);
   o.texture = tex;

   return o;
}