#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObjects.h"
//#include "CollisionCounter.h"
#include "Player.h"
#include "Enemies.h"
#include "assert.h"

#define TESTING_MULTITHREAD

class GameWorld
{
public:
	static void createInstance(sf::RenderWindow* window)
	{
		ms_gameWorld = new GameWorld(window);
	}

	static void destroyInstance()
	{
		delete ms_gameWorld;
	}

	void PostInit();

	static GameWorld* Instance()
	{
		assert(ms_gameWorld && "GameWorld Instance wasn't properly created!");
		return ms_gameWorld;
	}

	~GameWorld();

	void update(float DeltaTime);
	void draw(sf::RenderWindow* window);

	Player& GetPlayer() { return *m_player; }
	std::vector<GameObject*>& GetCollidableObjects() { return m_collidableObjects; };


private:
	GameWorld(sf::RenderWindow* window);

	void startGame();
	void EndGame();

	Player* m_player;
	Boss* m_boss;

	//CollisionCounter m_collisionCounter;
	sf::Font m_font;
	sf::Text m_victory, m_loss, m_restart;
	sf::Text m_health, m_rounds;

	std::vector<GameObject*> m_gameObjects = {};
	std::vector<GameObject*> m_collidableObjects = {};

	bool m_blurred = false;
	sf::RectangleShape m_rectangle;

	static GameWorld* ms_gameWorld;

	bool m_active = false;
	bool m_won = false;

	sf::Sprite m_arena;
};
