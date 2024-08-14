#include "GameState.h"
#include "GameStateManager.h"
#include "GameWorld.h"
//#include "FontManager.h"
//#include "SoundManager.h"

void GameState_Playing::onEnter()
{
	//SoundManager::getInstance().playGameStart();
}

void GameState_Playing::updateState()
{
	//#TODO, Bohdan: Add pause transition, gameOver transition
}

void GameState_Playing::update(float DeltaTime)
{
	m_GameWorld->update(DeltaTime);
}

void GameState_Playing::draw(sf::RenderWindow* window)
{
	m_GameWorld->draw(window);
}