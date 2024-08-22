#include "GameWorld.h"
#include "iostream"

#include "GameObjects.h"
#include "Enemies.h"
#include "Map.h"
#include "Textures.h"

GameWorld* GameWorld::ms_gameWorld = nullptr;

GameWorld::GameWorld(sf::RenderWindow* window)
{
    m_font.loadFromFile("arial.ttf");
    
    Textures* textures = Textures::Instance();
    Map map = Map::GetInstance();
    Minion* minion1 = new Minion(textures->getTexture("minion"));
    Minion* minion2 = new Minion(textures->getTexture("minion"));
    std::vector<Minion*> minions = { minion1, minion2 };
    std::vector<sf::Vector2f> spawns = { map.getPositionFromTile({0,7}), map.getPositionFromTile({16,7})};
    std::vector<sf::Vector2f> cannons = 
    { map.getPositionFromTile({2,0}), map.getPositionFromTile({5,0}), map.getPositionFromTile({9,0}), map.getPositionFromTile({14,0}) };
    m_boss = new Boss(minions, spawns, cannons, textures->getTexture("boss"));
    m_player = new Player(textures->getTexture("player"));

    m_gameObjects.push_back(m_player);
    m_gameObjects.push_back(minion1);
    m_gameObjects.push_back(minion2);
    m_gameObjects.push_back(m_boss);

    m_collidableObjects.push_back(m_player);
    m_collidableObjects.push_back(minion1);
    m_collidableObjects.push_back(minion2);
    m_collidableObjects.push_back(m_boss);

    m_victory.setFont(m_font);
    m_victory.setString("Victory achieved");
    m_victory.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_victory.setCharacterSize(60);
    m_victory.setPosition(map.getPositionFromTile({ 8, 4 }));
    m_victory.setFillColor(sf::Color::Black);

    m_loss.setFont(m_font);
    m_loss.setString("You died");
    m_loss.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_loss.setCharacterSize(60);
    m_loss.setPosition(map.getPositionFromTile({ 8, 4 }));
    m_loss.setFillColor(sf::Color::Black);

    m_restart.setFont(m_font);
    m_restart.setString("Press 'R' to restart or 'Esc' to exit");
    m_restart.setCharacterSize(24);
    m_restart.setPosition(map.getPositionFromTile({ 8, 5 }));
    m_restart.setFillColor(sf::Color::Black);

    m_rounds.setFont(m_font);
    m_rounds.setString("");
    m_rounds.setCharacterSize(24);
    m_rounds.setPosition(map.getPositionFromTile({ 0, 7 }));
    m_rounds.setFillColor(sf::Color::Black);

    
    m_health.setFont(m_font);
    m_health.setCharacterSize(24);
    m_health.setPosition(map.getPositionFromTile({ 0, 0 }));
    m_health.setFillColor(sf::Color::Black);
    

    startGame();
}

void GameWorld::startGame()
{
    Map map = Map::GetInstance();
    m_active = true;
    m_won = 0;
    m_boss->spawn(map.getPositionFromTile({ 16,1 }));
    m_player->spawn(map.getPositionFromTile({ 2,7 }));
}

void GameWorld::EndGame()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->despawn();
    }
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
    for (auto gameObject : m_gameObjects)
    {
        delete gameObject;
    }
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
    if (m_active)
    {
        for (size_t i = 0; i < m_gameObjects.size(); i++)
        {
            if (m_gameObjects[i]->isActive())
                m_gameObjects[i]->update(DeltaTime);
        }
        if (!m_player->isActive())
        {
            m_active = false;
            m_won = false;
            EndGame();
        }
        else if (!m_boss->isActive())
        {
            m_active = false;
            m_won = true;
            EndGame();
        }
        
        m_rounds.setString(std::to_string(m_player->getRounds()));
        m_health.setString(std::to_string(int(m_player->getHealth())));
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
        {
            startGame();
        }
    }
}

void GameWorld::draw(sf::RenderWindow* window)
{
    Map::GetInstance().draw(window);

    for (GameObject* object : m_gameObjects)
    {
        if (object->isActive())
        {
            object->draw(window);
            window->draw(m_rounds);
            window->draw(m_health);
        }
    }
    if (!m_active)
    {
        if (m_won)
        {
            window->draw(m_victory);
        }
        else
        {
            window->draw(m_loss);
        }
        window->draw(m_restart);
    }
}
