#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include <iostream>

void Player::handleRotation(float angle, float tickRate, bool isStrafing) {
    if (isStrafing) {
        return;
    }
    float rotDelta = this->rotationSpeed * tickRate;
    float deltaAngle = std::fmod(angle - this->angle + 540.0f, 360.0f) - 180.0f;
    if (std::abs(deltaAngle) <= rotDelta) {
            this->angle = angle;
        } else {
            this->angle += rotDelta * glm::sign(deltaAngle);
        }
    this->angle = std::fmod(this->angle + 360.0f, 360.0f); // normalize player angle
}

void Player::update(const InputState &inputs, GameState &gs, const Resources &res, double tickRate) {
    
    // do things based on inputs
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

    if (inputs.current & Lock) { // if locked, we want to slow down
        desiredVel = glm::vec2(0.0f);
    }

    glm::vec2 delta = desiredVel - this->vel;
    float distance = glm::length(delta);
    float maxDelta = this->acc.x * tickRate;

    if (distance <= maxDelta) {
        this->vel = desiredVel;
    } else {
        this->vel += glm::normalize(delta) * maxDelta;
    }

    

    direction facing;
    if (glm::length(inputDir) == 0.0f) {
        facing = this->dir;
    } else {
        // find desired angle
        float angle = glm::degrees(std::atan2(inputDir.x, -inputDir.y));
        angle = std::fmod(angle + 360.0f, 360.0f); // normalize

        this->handleRotation(angle, tickRate, inputs.current & Strafe); // if not strafing, rotate
        facing = static_cast<direction>(static_cast<int>((this->angle + 22.5f) / 45.0f) % 8); // get direction
        this->dir = facing;
        
    }
    //std::cout << "Facing: " << facing << " PlayerAngle: " << this->angle << std::endl;
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

    Object::update(gs, res, tickRate); // do generic update

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
    SDL_FlipMode flipMode = this->flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; // flip sprite?
    SDL_RenderTextureRotated(state.renderer, res.tileSet, &src, &dst, 0, nullptr, flipMode);
    this->drawDebug(state, gs);
}