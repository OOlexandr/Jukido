#pragma once
#include "GameObjects.h"

class Minion : public GameObject
{
public:
    Minion(sf::Texture* texture);

    void PostInit() override;
    void spawn(sf::Vector2f position) override;
};

class Boss : public GameObject
{
public:
    Boss(const std::vector<Minion*>& minions, std::vector<sf::Vector2f> spawn_points, sf::Texture* texture);
    Boss() {}

    void PostInit() override;
    void spawn(sf::Vector2f position) override;

protected:
    std::vector<Minion*> m_minions;
    std::vector<sf::Vector2f> m_spawn_points;
};