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
        bool flipSprite; // should we flip the sprite?

        virtual void update(const SDLState &state, GameState &gs, const Resources &res, float deltaTime);
        Player() : Object() {
            maxSpeed = 250.0f;
            isBeingMoved = false;
            dir = U;
            type = OBJ_PLAYER;
            flipSprite = false;
        }
        Player(glm::vec2 pos_, int tileID_) : Object(pos_, tileID_) {
            maxSpeed = 250.0f;
            isBeingMoved = false;
            dir = U;
            type = OBJ_PLAYER;
            flipSprite = false;
        }
        virtual ~Player() {}
        void draw(const SDLState &state, GameState &gs, const Resources &res);
};
