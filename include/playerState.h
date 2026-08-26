#pragma once

class SDLState;
class GameState;
class Player;
class Resources;
class InputState;

enum playerStateValue {
    NO_STATE,
    IDLE,
    WALK,
    LOCK
};

class PlayerState {
    public:
        playerStateValue stateVal; // enum for state value
        virtual ~PlayerState() = default;
        // virtual void draw(const SDLState &state, GameState &gs) {} // do nothing
        // Generic handlers (The player's state will call these by default if they don't have a new version defined, mostly for enter/exit)
        virtual PlayerState* update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate) { return nullptr; }
        virtual void enter(GameState &gs, const Resources &res, Player &p) {}
        virtual void exit(GameState &gs, const Resources &res, Player &p) {}
        PlayerState() {
            stateVal = NO_STATE; // if it's ever this we have a problem
        }
};

class IdleState : public PlayerState {
    public:
        PlayerState* update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate);
        void enter(GameState &gs, const Resources &res, Player &p);
        void exit(GameState &gs, const Resources &res, Player &p) {} // do nothing
        IdleState() {
            stateVal = IDLE;
        }
};

class WalkState : public PlayerState {
    public:
        PlayerState* update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate);
        void enter(GameState &gs, const Resources &res, Player &p);
        void exit(GameState &gs, const Resources &res, Player &p) {} // do nothing 
        WalkState() {
            stateVal = WALK;
        }
};

class LockState : public PlayerState {
    public:
        PlayerState* update(InputState &inputs, GameState &gs, const Resources &res, Player &p, double tickRate);
        void enter(GameState &gs, const Resources &res, Player &p);
        void exit(GameState &gs, const Resources &res, Player &p) {} // do nothing 
        LockState() {
            stateVal = LOCK;
        }
};

namespace States {
    extern IdleState idle;
    extern WalkState walk;
    extern LockState lock;
};