#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObjects.h"
//#include "CollisionCounter.h"
#include "Player.h"
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

	void blur();
	void unblur();

	void update(float DeltaTime);
	void draw(sf::RenderWindow* window);

	Player& GetPlayer() { return player; }
	std::vector<GameObject*>& GetCollidableObjects() { return m_collidableObjects; };


private:
	GameWorld(sf::RenderWindow* window);

	Player player;
	//CollisionCounter m_collisionCounter;

	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_collidableObjects;

	bool m_blurred = false;
	sf::RectangleShape m_rectangle;

	static GameWorld* ms_gameWorld;
};
