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
    GameObject(const char* textureFileName);

    virtual void PostInit() {}
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow* window);

    //Let's consider for now EVERY GameObject have Position and ONE Sprite
    //It may change in future, for example we will need GameObject without physical/visual body represantation
    //or with several sprites combined
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void updatePosition(const sf::Vector2f& deltaPosition);

    sf::Vector2f getSize() const;
    sf::Sprite* getSprite();

protected:
    //TODO, Bohdan: Don't load texture every time for the same objects
    sf::Texture m_texture;
    sf::Sprite m_sprite;

protected:
    std::vector<class Component*> m_components;
};

enum class NPC_Behavior
{
    Static,
    Floating,
    RandomSnap,

    AI_StraightLine,
    AI_BestRoute,
    AI_OptimalRoute,

    Count
};


class NPC : public GameObject
{
public:
    NPC(const char* filename = "BOX.png", NPC_Behavior behavior = NPC_Behavior::Static);

    void PostInit() override;
    void update(float deltaTime) override;
    void floatTo(const sf::Vector2f& direction, float deltaTime);

private:
    void setRandomPosition(sf::Vector2u box);

private:
    //TODO, Bohdan: Split NPC_Behavior into several sub-classes/components
    NPC_Behavior m_behavior;
    sf::Clock m_randomClock;
    sf::Clock m_floatClock;

    sf::Vector2f m_floatDirection;
};