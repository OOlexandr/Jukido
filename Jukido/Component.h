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
    virtual void despawn() {};

    virtual ~Component() {};
};

class JumpComponent : public Component
{
public:
    JumpComponent(GameObject* object);
    void update(float dt) override;

    virtual bool jumpRequested() { return false; };

protected:

    GameObject* m_owner = nullptr;
    sf::Vector2f m_velocity;

    bool m_jumpPressedLastFrame = false;


    sf::Sound m_jumpSound;
    sf::SoundBuffer m_buffer;
};

class PlayerJumpComponent : public JumpComponent
{
public:
    PlayerJumpComponent(GameObject* player) : JumpComponent(player) {};

    bool jumpRequested() override;
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

class PlayerAtackComponent : public Component
{
public:
    PlayerAtackComponent(Player* player);
    ~PlayerAtackComponent();

    void update(float dt) override;

    void draw(sf::RenderWindow* window) override;

protected:
    void atackSword();

    void fire();

    Player* m_player = nullptr;
    std::vector<Projectile*> m_bullets;
    std::vector<Projectile*> m_slashes;

    bool m_atackPressedLastFrame = false;
    bool m_requested_atack = false;
    bool m_shootPressedLastFrame = false;
    bool m_requested_shoot = false;
    int m_combo = 0;
    float m_cooldown = 0;
};