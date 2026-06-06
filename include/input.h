#pragma once

struct SDLState;
struct GameState;
struct Resources;

enum Inputs : uint32_t {
    None = 0,

    Up = 1 << 0,
    Right = 1 << 1,
    Down = 1 << 2, 
    Left = 1 << 3,

    Strafe = 1 << 4,
    Lock = 1 << 5,

    Save = 1 << 29,
    Restore = 1 << 30
};

struct InputState {
    uint32_t current = 0;
    uint32_t pressed = 0;
    uint32_t released = 0;
};

class InputManager {
    public:
        InputState inputState; 
        void handleInput(const bool *keys); 
};

void input(SDLState& state, GameState& gs);