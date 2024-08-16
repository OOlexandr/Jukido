#include "Player.h"
#include "Map.h"
#include "Component.h"


Player::Player() : GameObject("MINECRAFT_SPRITE.png")
{
	//Make origin at the center of the sprite rectangle
	m_sprite.setOrigin(m_sprite.getGlobalBounds().getSize().x / 2,
		m_sprite.getGlobalBounds().getSize().y);

	setPosition(Map::GetInstance().getRandomValidPosition());
	m_components.push_back(new PlayerJumpComponent(this));
	m_components.push_back(new PlayerMovementComponent(this));
	m_components.push_back(new PlayerAtackComponent(this));
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);
}