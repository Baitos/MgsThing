#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include <iostream>

void Object::draw(const SDLState &state, GameState &gs, const Resources &res) {
    glm::vec2 tileSheetPos = glm::vec2(this->tileId % res.tileSetCols, this->tileId / res.tileSetCols);
    SDL_FRect src { // gets tile in tileSet
        .x = tileSheetPos.x * TILE_SIZE,
        .y = tileSheetPos.y * TILE_SIZE,
        .w = this->width,
        .h = this->height
    };
    SDL_FRect dst {
        .x = this->pos.x - gs.mapViewport.x,
        .y = this->pos.y - gs.mapViewport.y,
        .w = this->width,
        .h = this->height
    };
    SDL_RenderTexture(state.renderer, res.tileSet, &src, &dst);
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

void Object::update(const SDLState &state, GameState &gs, const Resources &res, float deltaTime) {
    this->pos += this->vel * deltaTime;

    // slow down player in x direction
    const float factorX = this->vel.x > 0 ? -1.0f : 1.0f;
    float amountX = factorX * this->acc.x * deltaTime;
    if (std::abs(this->vel.x) < std::abs(amountX)) {
        this->vel.x = 0;         
    }
    else {
        this->vel.x += amountX;
    }

    const float factorY = this->vel.y > 0 ? -1.0f : 1.0f;
    float amountY = factorY * this->acc.y * deltaTime;
    if (std::abs(this->vel.y) < std::abs(amountY)) {
        this->vel.y = 0;         
    }
    else {
        this->vel.y += amountY;
    }
}