#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Projectile.h"

class GameObject;
class Player;

class Component
{
public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow* window) {}

    virtual ~Component() {};
};

class PlayerJumpComponent : public Component
{
public:
    PlayerJumpComponent(Player* player);
    void update(float dt) override;

    bool jumpRequested();

private:

    Player* m_player = nullptr;
    sf::Vector2f m_velocity;

    bool m_jumpPressedLastFrame = false;


    sf::Sound m_jumpSound;
    sf::SoundBuffer m_buffer;
};

class PlayerMovementComponent : public Component
{
public:
    PlayerMovementComponent(Player* player) : m_player(player) {}
    void update(float dt) override;

private:
    Player* m_player = nullptr;
};

class ShowObjectOriginComponent : public Component
{
public:
    ShowObjectOriginComponent(GameObject* gameObject);

    void update(float dt) override;
    void draw(sf::RenderWindow* window) override;

private:
    GameObject* m_gameObject = nullptr;
    sf::CircleShape m_circle;
};

class AIMoveToComponent : public Component
{
    // will be repurposed. Probably npcs will just move towards player.
public:
    AIMoveToComponent(GameObject* referenceObject, GameObject* targetObject);

protected:
    void moveTo(float dt, const sf::Vector2f& position);

protected:
    GameObject* m_referenceObject = nullptr;
    GameObject* m_targetObject = nullptr;

    unsigned m_speed = 400.0f;
    unsigned m_minimalDistance = 20.0f;
};

class AIMoveStraightLineComponent : public AIMoveToComponent
{
    //Most likely useless
public:
    using AIMoveToComponent::AIMoveToComponent;

    void update(float dt) override;
};

class PlayerAtackComponent : public Component
{
public:
    PlayerAtackComponent(Player* player);

    void update(float dt) override;

    void draw(sf::RenderWindow* window) override;

protected:
    Player* m_player = nullptr;
    Projectile* m_sword_slash = nullptr;
};