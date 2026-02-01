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


    // get toTarget direction as a vector
    Vector2 toTarget{Vector2Subtract(target->getScreenPos(), screenPos)};

    // normalise toTarget
    toTarget = Vector2Normalize(toTarget);

    // multiply normalised vector by speed and deltaTime to get velocity
    toTarget = Vector2Scale(toTarget, speed);

    // move enemy toward the target
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}
