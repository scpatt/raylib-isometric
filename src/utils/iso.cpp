//
// Created by sam.patterson on 18/05/2025.
//

#include "../constants.h"
#include "iso.h"
#include "raymath.h"

Vector2 GridToScreen(const int x, const int y, const int z = 0, const int logicalHeight = 0) {
    return {
        static_cast<float>((x - y) * TILE_HALF_WIDTH),
        static_cast<float>((x + y) * TILE_HALF_HEIGHT - (z * logicalHeight))
    };
}

bool IsPointInTileDiamond(const Vector2 point, const Vector2 tileTopLeft) {
    const float localX = point.x - tileTopLeft.x;
    const float localY = point.y - tileTopLeft.y;

    const float xNorm = fabsf(localX - TILE_HALF_WIDTH) / TILE_HALF_WIDTH;
    const float yNorm = fabsf(localY - TILE_HALF_HEIGHT) / TILE_HALF_HEIGHT;

    return (xNorm + yNorm) <= 1.0f;
}

Vector2 ScreenToGrid(const Vector2 point) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            const Vector2 tilePos = GridToScreen(x, y, 0);

            const Rectangle bounds = {
                tilePos.x,
                tilePos.y,
                static_cast<float>(TILE_WIDTH),
                static_cast<float>(TILE_HEIGHT)
            };

            if (!CheckCollisionPointRec(point, bounds))
                continue;

            if (IsPointInTileDiamond(point, tilePos)) {
                return {
                    static_cast<float>(x),
                    static_cast<float>(y)
                };
            }
        }
    }

    return {
        -1,
        -1
    };
}