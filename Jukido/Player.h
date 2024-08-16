#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player();
    void update(float deltaTime) override;

    float getSpeed() const { return m_speed; }

private:
    float m_speed = 1000.0f;
};