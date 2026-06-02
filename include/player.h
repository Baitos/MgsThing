#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "animation.h"
#include "resources.h"
#include "globals.h"
#include "object.h"

struct SDLState;
struct GameState;
struct Resources;

enum direction {
    U,
    UR,
    R,
    DR,
    D,
    DL,
    L,
    UL
};

class Player : public Object {   
    public:
        float maxSpeed;
        bool isBeingMoved; // set to true if an input is being held
        direction dir; // which way to face sprite
        float angle; // angle player is facing
        bool flipSprite; // should we flip the sprite?
        float rotationSpeed; // how many degrees should the player character rotate in a second?

        Player() : Object() {
            maxSpeed = 250.0f;
            isBeingMoved = false;
            dir = U;
            type = OBJ_PLAYER;
            angle = 0.0f;
            flipSprite = false;
            rotationSpeed = 360.0f; // should be half a second at 360 to turn around
        }
        Player(glm::vec2 pos_, int tileID_) : Object(pos_, tileID_) {
            maxSpeed = 250.0f;
            isBeingMoved = false;
            dir = U;
            type = OBJ_PLAYER;
            angle = 0.0f;
            flipSprite = false;
            rotationSpeed = 360.0f;
        }
        virtual ~Player() {}
        virtual void update(const InputState &inputs, GameState &gs, const Resources &res, double tickRate);
        void draw(const SDLState &state, GameState &gs, const Resources &res);
        void handleRotation(float angle, float tickRate, bool isStrafing);
};
