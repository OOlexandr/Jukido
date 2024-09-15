#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObjects.h"
//#include "CollisionCounter.h"

class GameStateManager;

class GameWorld;

class GameState
{
public:
	GameState(GameStateManager& context) : m_gameStateManager(context) {}

	virtual void onEnter() {} //To add initialization during state enter
	virtual void onExit() {} //To add deinitialization during state exit

	virtual void updateState() = 0;
	virtual void update(float DeltaTime) = 0;
	virtual void draw(sf::RenderWindow* window) = 0;

protected:
	GameStateManager& m_gameStateManager;
};

class GameState_Playing : public GameState
{
public:
	GameState_Playing(GameStateManager& context, GameWorld* gameWorld) : GameState(context), m_GameWorld(gameWorld) {}

	void onEnter() override;

	void updateState() override;
	void update(float DeltaTime) override;
	void draw(sf::RenderWindow* window) override;

private:
	GameWorld* m_GameWorld;

	bool m_pressedLastFrame = true;
};