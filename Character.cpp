#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
    : windowWidth{winWidth}, windowHeight{winHeight}
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * height)};
}
void Character::tick(float deltaTime)
{

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);

    Vector2 origin{0.f, 0.f};
    Vector2 offset{0.f, 0.f};
    float weaponRotation{0.f};
    if (rightLeft > 0.f)
    {
       origin = {0.f, static_cast<float>(weapon.height) * scale};
       offset = {35.f, 55.f};
       weaponCollisonRec = {
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale
       };
       weaponRotation = 35.f;
    }
    else
    {
        origin = {static_cast<float>(weapon.width) * scale, static_cast<float>(weapon.height) * scale};
        offset = {25.f, 55.f};
         weaponCollisonRec = {
          getScreenPos().x + offset.x - weapon.width * scale,
          getScreenPos().y + offset.y - weapon.height * scale,
          weapon.width * scale,
          weapon.height * scale
         };
        weaponRotation = -35.f;
    }
    
    // draw weapon
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y,
        scale * static_cast<float>(weapon.width),
        scale * static_cast<float>(weapon.height)};
    DrawTexturePro(weapon, source, dest, origin, weaponRotation, WHITE);

    DrawRectangleLines(
        getCollissionRec().x,
        getCollissionRec().y,
        getCollissionRec().width,
        getCollissionRec().height,
        RED);

    DrawRectangleLines(
        weaponCollisonRec.x,
        weaponCollisonRec.y,
        weaponCollisonRec.width,
        weaponCollisonRec.height,
        BLUE);
}
