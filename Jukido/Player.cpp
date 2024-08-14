#include "Player.h"
#include "Map.h"
#include "Component.h"


Player::Player() : GameObject("MINECRAFT_SPRITE.png")
{
	//Make origin at the center of the sprite rectangle
	m_sprite.setOrigin(m_sprite.getGlobalBounds().getSize().x / 2,
		m_sprite.getGlobalBounds().getSize().y / 2);

	setPosition(Map::GetInstance().getRandomValidPosition());
	m_components.push_back(new PlayerJumpComponent(this));
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);

	//#TODO, Bohdan: Each can be its own component
	handleMovemenent(deltaTime);
}

void Player::handleMovemenent(float deltaTime)
{
	const float MoveDelta = m_speed * deltaTime;

	float deltaX = 0;
	float deltaY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		deltaX += MoveDelta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		deltaX -= MoveDelta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		deltaY -= MoveDelta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		deltaY += MoveDelta;
	}

	updatePosition({ deltaX, deltaY });
}