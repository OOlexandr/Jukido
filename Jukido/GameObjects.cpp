#include "GameObjects.h"
#include "Component.h"
#include "Behaviour.h"
#include "Map.h"
#include "GameWorld.h"

//Enable if needed
//#define NPC_DEBUG_POSITION

GameObject::GameObject(const sf::Texture* texture)
{
	m_texture = *texture;
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin({ float(m_texture.getSize().x / 2), float(m_texture.getSize().y / 2) });
}

GameObject::~GameObject()
{
	for (Component* c : m_components)
	{
		delete c;
	}
}

void GameObject::update(float deltaTime)
{
	for (Component* component : m_components)
	{
		component->update(deltaTime);
	}

	updatePosition(deltaTime);
}

void GameObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);

	for (Component* component : m_components)
	{
		component->draw(window);
	}
}

//Let's consider for now EVERY GameObject have Position and ONE Sprite
//It may change in future, for example we will need GameObject without physical/visual body represantation
//or with several sprites combined
void GameObject::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

//#TODO, Bohdan: Make it a RestrictByMapComponent so there're objects that are restricted and not by Map Tiles
void GameObject::updatePosition(float dt)
{
	sf::Vector2f position = getPosition();
	if (m_current_speed.x > 0)
	{
		if (!Map::GetInstance().isTileBlocked({ position.x + m_current_speed.x * dt + m_sprite.getLocalBounds().width / 2, position.y }))
		{
			position.x += m_current_speed.x * dt;
		}
	}
	else
	{
		if (!Map::GetInstance().isTileBlocked({ position.x + m_current_speed.x * dt - m_sprite.getLocalBounds().width / 2 , position.y }))
		{
			position.x += m_current_speed.x * dt;
		}
	}

	if (m_current_speed.y > 0)
	{
		if (!Map::GetInstance().isTileBlocked({ position.x, position.y + m_current_speed.y * dt + m_sprite.getLocalBounds().height / 2 }))
		{
			position.y += m_current_speed.y * dt;
		}
		else
		{
			m_on_the_ground = true;
			m_current_speed.y = 0.f;
		}
	}
	else
	{
		if (!Map::GetInstance().isTileBlocked({ position.x, position.y + m_current_speed.y * dt - m_sprite.getLocalBounds().height / 2 }))
		{
			position.y += m_current_speed.y * dt;
		}
		else
		{
			m_current_speed.y = 0.f;
		}
	}

	if (!Map::GetInstance().isTileBlocked({ position.x, position.y + m_sprite.getLocalBounds().height / 2 + 10}))
	{
		m_on_the_ground = false;
	}

	setPosition(position);
}

sf::Vector2f GameObject::getSize() const
{
	return m_sprite.getLocalBounds().getSize();
}

sf::Sprite* GameObject::getSprite()
{
	return &m_sprite;
}

void GameObject::spawn(sf::Vector2f position)
{
	m_active = true;
	setPosition(position);
}

void GameObject::despawn()
{
	m_active = false;
	setPosition({ 0.f,0.f });
	for (Component* c : m_components)
	{
		c->despawn();
	}
}

void GameObject::takeDamage(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		despawn();
	}
}