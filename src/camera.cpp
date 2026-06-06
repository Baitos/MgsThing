#include "../include/camera.h"
#include "../include/draw.h"
#include "../include/gameState.h"
#include "../include/globals.h"
#include <algorithm>
#include <vector>

void Camera::renderOnscreenTiles(const SDLState& state, GameState& gs, Resources& res, std::vector<Object>& tileLayer, int mapWidth, int mapHeight) {
    int startX = std::max(0, (int)this->x / TILE_SIZE);
    int endX = std::min(mapWidth, (int)(this->x + this->w) / TILE_SIZE + 1);
    int startY = std::max(0, (int)this->y / TILE_SIZE);
    int endY = std::min(mapHeight, (int)(this->y + this->h) / TILE_SIZE + 1);

    for (int ty = startY; ty < endY; ty++) {
        for (int tx = startX; tx < endX; tx++) {
            Object& tile = tileLayer[ty * mapWidth + tx];
                if (tile.type != NO_OBJ_TYPE) {
                    tile.draw(state, gs, res, *this);
                }
        }
    }
}