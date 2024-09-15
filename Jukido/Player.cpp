#include "Player.h"
#include "Map.h"
#include "Textures.h"
#include "Component.h"


void Player::PostInit()
{
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

void Player::spawn(sf::Vector2f position)
{
	GameObject::spawn(position);
	m_n_bullets = 0;
	m_health = 3;
}
