#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include <iostream>

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
    glm::vec2 desiredVel = inputDir * this->maxSpeed;
    glm::vec2 delta = desiredVel - this->vel;
    float distance = glm::length(delta);
    float maxDelta = this->acc.x * deltaTime;

    if (distance <= maxDelta) {
        this->vel = desiredVel;
    } else {
        this->vel += glm::normalize(delta) * maxDelta;
    }


    //std::cout << "VelX: " << this->vel.x << " VelY: " << this->vel.y << std::endl;
    direction facing;
    if (glm::length(inputDir) == 0) {
        facing = this->dir;
    } else {
        float angle = glm::degrees(glm::atan(inputDir.y, inputDir.x)) + 90.0f;
        angle = std::fmod(angle + 360.0f, 360.0f); // normalize
        facing = static_cast<direction>(static_cast<int>((angle + 22.5f) / 45.0f) % 8); // get direction
        this->dir = facing;
        
    }
    //std::cout << facing << std::endl;
    switch (facing) {
        case U:
        {
            this->tileId = 4;
            flipSprite = false;
            break;
        }
        case UR:
        {
            this->tileId = 5;
            flipSprite = false;
            break;
        }
        case R:
        {
            this->tileId = 6;
            flipSprite = false;
            break;
        }
        case DR:
        {
            this->tileId = 7;
            flipSprite = false;
            break;
        }
        case D:
        {
            this->tileId = 8;
            flipSprite = false;
            break;
        }
        case DL:
        {
            this->tileId = 7;
            flipSprite = true;
            break;
        }
        case L:
        {
            this->tileId = 6;
            flipSprite = true; 
            break;
        }
        case UL:
        {
            this->tileId = 5;
            flipSprite = true; 
            break;
        }
    }

    this->pos += this->vel * deltaTime;
}

void Player::draw(const SDLState &state, GameState &gs, const Resources &res) {
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
    SDL_FlipMode flipMode;
    if (this->flipSprite) {
        flipMode = SDL_FLIP_HORIZONTAL;
    } else {
        flipMode = SDL_FLIP_NONE;
    }
    SDL_RenderTextureRotated(state.renderer, res.tileSet, &src, &dst, 0, nullptr, flipMode);
    this->drawDebug(state, gs);
}