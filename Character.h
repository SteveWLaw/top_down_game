#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponRec() { return weaponCollisonRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int windowWidth;
    int windowHeight;
    Texture2D weapon{LoadTexture("textures/characters/weapon_sword.png")};
    Rectangle weaponCollisonRec{35.f, 20.f, 30.f, 40.f};
    float health{100.f};
};

#endif