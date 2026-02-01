#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)

{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;
    // get direction to target
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    BaseCharacter::tick(deltaTime);

    // deal damage to target if colliding
    if (CheckCollisionRecs(getCollissionRec(), target->getCollissionRec()))
    {
        target->takeDamage(damagePerSecond * deltaTime);
    }

    // draw enemy collision rectangle (for debugging)
    DrawRectangleLines(
        getCollissionRec().x,
        getCollissionRec().y,
        getCollissionRec().width,
        getCollissionRec().height,
        BLACK);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}