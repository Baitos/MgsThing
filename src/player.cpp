#include "../include/object.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/camera.h"
#include "../include/playerState.h"
#include <iostream>

Player::Player(glm::vec2 pos_, int tileID_) : Object(pos_, tileID_) {
    type = OBJ_PLAYER;
    vel = acc = glm::vec2(0);
    solid = true;
    collider = {
        .x = 3,
        .y = 0,
        .w = 26,
        .h = (float)TILE_SIZE
    };
    playerState = &States::idle; // fsm again, start in idle
}

Player::Player() : Object() {
    type = OBJ_PLAYER;
    solid = true;
    collider = {
        .x = 3,
        .y = 0,
        .w = 26,
        .h = (float)TILE_SIZE
    };
    playerState = &States::idle; // fsm again, start in idle
}

void Player::handleRotation(float angle, double tickRate, bool isStrafing) {
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

void Player::update(InputState &inputs, GameState &gs, const Resources &res, double tickRate) {
    PlayerState* pState = this->playerState->update(inputs, gs, res, (*this), tickRate);
    this->handleState(pState, gs, res);
    
    const int SUBSTEPS = 8; // maybe a bit excessive but this seems to work fine
    double subTickRate = tickRate / SUBSTEPS;
    for (int i = 0; i < SUBSTEPS; i++) {
        Object::update(gs, res, subTickRate); // do generic update
        this->checkCollision(gs, res, subTickRate); // check collision
    }
}

void Player::draw(const SDLState &state, GameState &gs, const Resources &res, Camera& cam) {
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
    SDL_FlipMode flipMode = this->flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; // flip sprite?
    SDL_RenderTextureRotated(state.renderer, res.tileSet, &src, &dst, 0, nullptr, flipMode);
    this->drawDebug(state, gs, cam);
}

void Player::handleState(PlayerState* &pState, GameState &gs, const Resources &res) {
    if (pState == nullptr) {
        return;
    }
    this->playerState->exit(gs, res, (*this)); // exit fn for old state
    this->playerState = pState;
    this->playerState->enter(gs, res, (*this)); // enter fn for new state
}