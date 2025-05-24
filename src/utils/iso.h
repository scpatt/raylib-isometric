//
// Created by sam.patterson on 18/05/2025.
//

#ifndef ISO_H
#define ISO_H

#include "raylib.h"

Vector2 GridToScreen(int x, int y, int z, int logicalHeight);
Vector2 ScreenToGrid(Vector2 point);
bool IsPointInTileDiamond(Vector2 point, Vector2 tileTopLeft);

#endif //ISO_H
