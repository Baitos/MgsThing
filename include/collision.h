#pragma once
#include "object.h"

struct GameState;
struct Player;

Object getTileOnTileMap(int x, int y, GameState &gs);
bool intersectAABB(const SDL_FRect &a, const SDL_FRect &b, glm::vec2 &overlap);