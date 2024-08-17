#include "GameWorld.h"

#include "GameObjects.h"
#include "Map.h"

GameWorld* GameWorld::ms_gameWorld = nullptr;

GameWorld::GameWorld(sf::RenderWindow* window)
{
    NPC* npc1 = new NPC("stone.png", NPC_Behavior::AI_BestRoute); //center of the game window
    NPC* npc2 = new NPC("stone.png", NPC_Behavior::AI_BestRoute); //center of the game window
    NPC* npc3 = new NPC("stone.png", NPC_Behavior::AI_BestRoute); //center of the game window



    m_gameObjects.push_back(&m_player);
    m_gameObjects.push_back(npc1);
    m_gameObjects.push_back(npc2);
    m_gameObjects.push_back(npc3);

    m_collidableObjects.push_back(npc1);
    m_collidableObjects.push_back(npc2);
    m_collidableObjects.push_back(npc3);
    m_collidableObjects.push_back(&m_player);
}

void GameWorld::PostInit()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->PostInit();
    }
}

GameWorld::~GameWorld()
{
    //TODO, Bohdan: Delete memory used
}


bool checkCollision(const sf::Sprite* sprite1, const sf::Sprite* sprite2)
{
    if (sprite1 && sprite2)
    {
        return sprite1->getGlobalBounds().intersects(sprite2->getGlobalBounds());
    }

    assert(false && "Invalid sprites passed for the collision check");
    return false;
}


void GameWorld::update(float DeltaTime)
{
    //Update all game objects
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update(DeltaTime);
    }
}

void GameWorld::draw(sf::RenderWindow* window)
{
    Map::GetInstance().draw(window);

    for (GameObject* object : m_gameObjects)
    {
        object->draw(window);
    }
}
