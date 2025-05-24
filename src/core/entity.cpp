#include "Entity.h"
#include "../utils/iso.h"
#include "../utils/texture_manager.h"

Entity::Entity(const int x, const int y, const int z, const int logicalHeight, const std::string& texturePath) :
    gridX(x),
    gridY(y),
    gridZ(z),
    logicalHeight(logicalHeight),
    texture(TextureManager::getInstance().getTexture(texturePath)),
    tint(RED),
    rotation(0.0f),
    scale(1.0f),
    screenPosition({0, 0})
{
    Entity::UpdateScreenPosition();
}

void Entity::UpdateScreenPosition() {
    screenPosition = GridToScreen(gridX, gridY, gridZ, logicalHeight);
}

void Entity::SetGridPosition(const int x, const int y, const int z) {
    gridX = x;
    gridY = y;
    gridZ = z;

    UpdateScreenPosition();
}

void Entity::GetGridPosition(int& x, int& y, int& z) const {
    x = gridX;
    y = gridY;
    z = gridZ;
}

void Entity::Render() const {
    DrawTextureEx(texture, screenPosition, rotation, scale, tint);
}

int Entity::GetRenderOrder() const {
    return gridX + gridY + gridZ;
}