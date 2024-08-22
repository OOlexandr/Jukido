#pragma once
#include <SFML/Graphics.hpp>

class Component;

//TODO: Bohdan
enum class VisibilityPriority
{
    p1,
    p2,
    p3,
    p4,
    Background,
    Middle,
    Front
};

class GameObject
{
public:
    GameObject(const sf::Texture* texture);
    GameObject() {};

    virtual void PostInit() {}
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow* window);

    //Let's consider for now EVERY GameObject have Position and ONE Sprite
    //It may change in future, for example we will need GameObject without physical/visual body represantation
    //or with several sprites combined
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    virtual void updatePosition(float dt);

    sf::Vector2f getSize() const;
    sf::Sprite* getSprite();

    sf::Vector2f getCurrentSpeed() const { return m_current_speed; }
    float getSpeed() const { return m_speed; }
    void updateSpeedX(float speed_x) { m_current_speed.x = speed_x; }
    void updateSpeedY(float speed_y) { m_current_speed.y = speed_y; }

    bool isOnTheGround() { return m_on_the_ground; }
    bool isActive() { return m_active; }
    virtual void spawn(sf::Vector2f position);
    virtual void despawn();

    virtual void takeDamage(float damage);
    float getHealth() { return m_health; }

    virtual void addRounds(float add) {}

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

protected:
    std::vector<class Component*> m_components;
    bool m_on_the_ground = true;
    sf::Vector2f m_current_speed = { 0.0f, 0.0f };
    float m_speed = 0;
    float m_health = 0;
    bool m_active = false;
};