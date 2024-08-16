#include "Projectile.h"
#include "Map.h"
#include "GameWorld.h"

Projectile::Projectile(const char* textureFileName, const GameObject* owner) : GameObject(textureFileName), m_owner(owner)
{
	m_sprite.setOrigin(0, m_sprite.getGlobalBounds().getSize().y);

	setPosition({ 0.0f, 0.0f });
}

void Projectile::update(float deltaTime)
{
	GameObject::update(deltaTime);
	setPosition(m_owner->getPosition());

	m_time_alive += deltaTime;
	if (m_time_alive >= m_longevity)
	{
		deactivate();
	}
}

void Projectile::DealDamage(GameObject* target)
{
	target->takeDamage(m_damage);
}

void Projectile::activate(sf::Vector2f position, float damage, sf::Vector2f direction, float longevity)
{
	//direction is a normalized vector
	setPosition(position);
	m_damage = damage;
	m_time_alive = 0;
	m_longevity = longevity;
	m_active = true;
}

void Projectile::deactivate()
{
	setPosition({ 0.0f, 0.0f });
	m_current_speed = { 0.0f, 0.0f };
	m_active = false;
}

void Slash::activate(sf::Vector2f position, float damage, sf::Vector2f direction, float longevity)
{
	Projectile::activate(position, damage, direction, longevity);
	if (direction.x > 0)
	{
		m_sprite.setScale({ 1.f, 1.f });
	}
	else
	{
		m_sprite.setScale({ -1.f, 1.f });
	}
}

void Slash::update(float deltaTime)
{
	Projectile::update(deltaTime);

	std::vector<GameObject*> targets = GameWorld::Instance()->GetCollidableObjects();
	for (GameObject* t : targets)
	{
		sf::FloatRect slash = m_sprite.getGlobalBounds();
		sf::FloatRect target = t->getSprite()->getGlobalBounds();
		
		if (slash.intersects(target))
		{
			t->takeDamage(m_damage);
		}
	}
}
