#include "Projectile.h"
#include "Map.h"
#include "GameWorld.h"
#include "MathHelper.h"

Projectile::Projectile(sf::Texture* texture, const GameObject* owner) : GameObject(texture), m_owner(owner)
{
	m_health = 1;
}

void Projectile::update(float deltaTime)
{
	GameObject::update(deltaTime);

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

void Projectile::activate(float damage, sf::Vector2f direction, float longevity)
{
	sf::Vector2f pos = m_owner->getPosition();
	setPosition(m_owner->getPosition());
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

void Projectile::despawn()
{
	deactivate();
}

Slash::Slash(sf::Texture* texture, const GameObject* owner) : Projectile(texture, owner)
{
	m_sprite.setOrigin(0, m_sprite.getGlobalBounds().getSize().y / 2);
}

void Slash::activate(float damage, sf::Vector2f direction, float longevity)
{
	m_hit_targets.clear();
	Projectile::activate(damage, direction, longevity);
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
		if (!(t == m_owner))
		{
			sf::FloatRect slash = m_sprite.getGlobalBounds();
			sf::FloatRect target = t->getSprite()->getGlobalBounds();

			if (slash.intersects(target) && !(std::find(m_hit_targets.begin(), m_hit_targets.end(), t) != m_hit_targets.end()))
			{
				t->takeDamage(m_damage);
				m_hit_targets.push_back(t);
			}
		}
	}
}

void Bullet::updatePosition(float dt)
{
	sf::Vector2f position = getPosition();
	if (!Map::GetInstance().isTileBlocked({ position.x + m_current_speed.x * dt, position.y }))
	{
		position.x += m_current_speed.x * dt;

	}
	else
	{
		deactivate();
		return;
	}

	if (!Map::GetInstance().isTileBlocked({ position.x, position.y + m_current_speed.y * dt }))
	{
		position.y += m_current_speed.y * dt;
	}
	else
	{
		deactivate();
		return;
	}


	setPosition(position);
}

void Bullet::activate(float damage, sf::Vector2f direction, float longevity)
{
	Projectile::activate(damage, direction, longevity);
	sf::Vector2f normalDirection = MathHelper::Normalize(direction);
	m_current_speed = normalDirection * m_speed;
}

void Bullet::update(float deltaTime)
{
	Projectile::update(deltaTime);

	std::vector<GameObject*> targets = GameWorld::Instance()->GetCollidableObjects();
	for (GameObject* t : targets)
	{
		if (!(t == m_owner))
		{
			sf::FloatRect slash = m_sprite.getGlobalBounds();
			sf::FloatRect target = t->getSprite()->getGlobalBounds();

			if (slash.intersects(target))
			{
				t->takeDamage(m_damage);
				deactivate();
				break;
			}
		}
	}
}
