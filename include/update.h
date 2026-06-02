#pragma once

struct SDLState;
struct GameState;
struct Resources;

void update(const SDLState& state, GameState& gs, const Resources& res, double tickRate);