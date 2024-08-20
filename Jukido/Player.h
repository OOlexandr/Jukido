#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player(sf::Texture* texture) : GameObject(texture) {}
    void PostInit() override;
    void update(float deltaTime) override;
};