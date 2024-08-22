#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player(sf::Texture* texture) : GameObject(texture) {}
    void PostInit() override;
    void update(float deltaTime) override;

    void addRounds(float add) override { m_n_bullets = std::min(m_n_bullets + add * 0.5f, 6.1f); } //6.1 to avoid it capping at 5.99999999999999999
    int getRounds() { return m_n_bullets; }
    void decreaseRounds() { m_n_bullets -= 1; }

    void spawn(sf::Vector2f position) override;

private:
    float m_n_bullets = 0;
};