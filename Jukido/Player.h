#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player();
    void update(float deltaTime) override;
};