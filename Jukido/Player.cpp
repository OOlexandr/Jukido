#include "Player.h"
#include "Map.h"
#include "Component.h"


Player::Player() : GameObject("MINECRAFT_SPRITE.png")
{
	setPosition(Map::GetInstance().getRandomValidPosition());
	m_components.push_back(new PlayerJumpComponent(this));
	m_components.push_back(new PlayerMovementComponent(this));
	m_components.push_back(new PlayerAtackComponent(this));
	m_health = 3;
	m_speed = 500.f;
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);
}