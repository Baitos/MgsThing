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
}

void Player::update(const SDLState &state, GameState &gs, const Resources &res, float deltaTime) {
    
    // do things based on inputs
    InputState inputs = state.im.inputState;
    glm::vec2 inputDir(0.0f);
    if (inputs.current & Up) {
        inputDir.y -= 1.0f;
    }
    if (inputs.current & Down) {
        inputDir.y += 1.0f;
    }
    if (inputs.current & Left) {
        inputDir.x -= 1.0f;
    }
    if (inputs.current & Right) {
        inputDir.x += 1.0f;
    }

    if (glm::dot(inputDir, inputDir) > 0.0f) { // normalize for diagonal movement
        inputDir = glm::normalize(inputDir);
    }

    // accelerate towards max velocity in inputted direction
    glm::vec2 desiredVelocity = inputDir * this->maxSpeed;
    glm::vec2 delta = desiredVelocity - this->vel;
    float distance = glm::length(delta);
    float maxDelta = this->acc.x * deltaTime;

    if (distance <= maxDelta) {
        this->vel = desiredVelocity;
    } else {
        this->vel += glm::normalize(delta) * maxDelta;
    }


    std::cout << "VelX: " << this->vel.x << " VelY: " << this->vel.y << std::endl;
    this->pos += this->vel * deltaTime;

    
}
