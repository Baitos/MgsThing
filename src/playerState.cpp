#include "../include/playerState.h"
#include "../include/player.h"
#include "../include/input.h"
#include <iostream>

IdleState States::idle;
WalkState States::walk;
LockState States::lock;

// contains tileID of character on tileSet based on direction (and if the sprite should flip)
const directionTable dirTable[8] = {
    {4, false},
    {5, false},
    {6, false},
    {7, false},
    {8, false},
    {7, true},
    {6, true},
    {5, true}
};

void handleDirectionalMovement(InputState &inputs, glm::vec2 &inputDir) {
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
}

PlayerState* IdleState::update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate) {
    if (inputs.current & (Up | Down | Left | Right)) { // if moving return walkState
        return &States::walk;
    }
    else if (inputs.current & Lock) { // if locking movement to to lock
        return &States::lock;
    }
    return nullptr;
}

void IdleState::enter(GameState &gs, const Resources &res, Player &p) {
    p.vel = glm::vec2(0.0f);
    std::cout << "Idle Enter\n";
}

PlayerState* WalkState::update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate) {
    // do things based on inputs
    if (inputs.current & Lock) { // if locking movement to to lock
        return &States::lock;
    }

    glm::vec2 inputDir(0.0f);
    handleDirectionalMovement(inputs, inputDir); 

    // accelerate towards max velocity in inputted direction
    glm::vec2 desiredVel = inputDir * p.maxSpeed;


    glm::vec2 delta = desiredVel - p.vel;
    float distance = glm::length(delta);
    float maxDelta = p.acc.x * tickRate;

    if (distance <= maxDelta) {
        p.vel = desiredVel;
    } else {
        p.vel += glm::normalize(delta) * maxDelta;
    }

    if (glm::length(p.vel) == 0.0f) {
        return &States::idle; // return idle state if overall velocity is 0
    }

    direction facing;
    if (glm::length(inputDir) == 0.0f) {
        facing = p.dir;
    } else {
        // find desired angle
        float angle = glm::degrees(std::atan2(inputDir.x, -inputDir.y));
        angle = std::fmod(angle + 360.0f, 360.0f); // normalize

        p.handleRotation(angle, tickRate, inputs.current & Strafe); // if not strafing, rotate
        facing = static_cast<direction>(static_cast<int>((p.angle + 22.5f) / 45.0f) % 8); // get direction
        p.dir = facing;
    }
    // go to lookup table for sprite based on direction
    p.tileId = dirTable[facing].tileID;
    p.flipSprite = dirTable[facing].flipSprite;
    return nullptr;
}

void WalkState::enter(GameState &gs, const Resources &res, Player &p) {
    std::cout << "Walk Enter\n";
}

PlayerState* LockState::update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate) {
    if (!(inputs.current & Lock)) { // if you let go, release lock state
        return &States::walk;
    }
    
    glm::vec2 inputDir(0.0f);
    handleDirectionalMovement(inputs, inputDir);

    glm::vec2 zeroVel = glm::vec2(0.0f);
    glm::vec2 delta = zeroVel - p.vel;
    float distance = glm::length(delta);
    float maxDelta = p.acc.x * tickRate;
    p.vel = zeroVel;
    if (distance <= maxDelta) {
        p.vel = zeroVel;
    } else {
        p.vel += glm::normalize(delta) * maxDelta;
    }

    direction facing;
    if (glm::length(inputDir) == 0.0f) {
        facing = p.dir;
    } else {
        // find desired angle
        float angle = glm::degrees(std::atan2(inputDir.x, -inputDir.y));
        angle = std::fmod(angle + 360.0f, 360.0f); // normalize

        p.handleRotation(angle, tickRate, false); // rotate (not strafing)
        facing = static_cast<direction>(static_cast<int>((p.angle + 22.5f) / 45.0f) % 8); // get direction
        p.dir = facing;
    }
    // go to lookup table for sprite based on direction
    p.tileId = dirTable[facing].tileID;
    p.flipSprite = dirTable[facing].flipSprite;

    return nullptr;
}

void LockState::enter(GameState &gs, const Resources &res, Player &p) {
    std::cout << "Lock Enter\n";
}