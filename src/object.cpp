#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/camera.h"
#include <iostream>

void Object::update(GameState &gs, const Resources &res, double tickRate) {    
    this->pos += this->vel * (float)tickRate;
}

void Object::draw(const SDLState &state, GameState &gs, const Resources &res, Camera& cam) {
    glm::vec2 tileSheetPos = glm::vec2(this->tileId % res.tileSetCols, this->tileId / res.tileSetCols);
    SDL_FRect src { // gets tile in tileSet
        .x = tileSheetPos.x * TILE_SIZE,
        .y = tileSheetPos.y * TILE_SIZE,
        .w = this->width,
        .h = this->height
    };
    SDL_FRect dst {
        .x = this->pos.x - cam.x,
        .y = this->pos.y - cam.y,
        .w = this->width,
        .h = this->height
    };
    SDL_RenderTexture(state.renderer, res.tileSet, &src, &dst);
    this->drawDebug(state, gs, cam);
}

void Object::drawDebug(const SDLState &state, GameState &gs, Camera& cam) {
    if (gs.debugMode && this->debug && this->solid) {
        SDL_FRect rectA {
            .x = this->pos.x + this->collider.x - cam.x, 
            .y = this->pos.y + this->collider.y - cam.y,
            .w = this->collider.w, 
            .h = this->collider.h
        };
        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 150);
        SDL_RenderFillRect(state.renderer, &rectA);

        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_NONE);
    }
}

/*void Object::drawDebugNearby(const SDLState &state, GameState &gs, Camera& cam) {
    if (gs.debugMode && this->debug) {
        SDL_FRect rectA {
            .x = this->pos.x + this->collider.x - cam.x, 
            .y = this->pos.y + this->collider.y - cam.y,
            .w = this->collider.w, 
            .h = this->collider.h
        };
        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(state.renderer, 0, 255, 0, 150);
        SDL_RenderFillRect(state.renderer, &rectA);

        SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_NONE);
    }
}*/