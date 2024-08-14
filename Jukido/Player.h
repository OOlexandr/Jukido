#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player();
    void update(float deltaTime) override;

private:
    void handleMovemenent(float deltaTime);

private:
    float m_speed = 1000.0f;
};