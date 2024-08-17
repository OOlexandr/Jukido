#include "Behaviour.h"
#include "GameWorld.h"
#include "MathHelper.h"

sf::Vector2f Behavior::getVectorToPlayer()
{
	return GameWorld::Instance()->GetPlayer().getPosition() - m_owner->getPosition();
}

void Behavior::update(float deltaTime)
{
	for (Projectile* p : m_projectiles)
	{
		if (p->isActive())
		{
			p->update(deltaTime);
		}
	}
	if (m_locked)
	{
		m_cooldown -= deltaTime;
		if (m_cooldown < 0)
		{
			m_locked = false;
		}
	}
	else
	{
		decision();
	}
}

void Behavior::draw(sf::RenderWindow* window)
{
	for (Projectile* p : m_projectiles)
	{
		if (p->isActive())
		{
			p->draw(window);
		}
	}
}

void Behavior::lock(float time)
{
	m_owner->updateSpeedX(0);
	m_locked = true;
	m_cooldown = time;
}

MinionBehavior::MinionBehavior(GameObject* owner) : Behavior(owner)
{
	m_slash = new Slash("RedSlash2.png", m_owner);
	m_projectiles.push_back(m_slash);
}

void MinionBehavior::move()
{
	float x = getVectorToPlayer().x;
	if (x > 0)
	{
		m_owner->updateSpeedX(m_owner->getSpeed());
	}
	else
	{
		m_owner->updateSpeedX(-m_owner->getSpeed());
	}
}

void MinionBehavior::atack(float damage = 1, float cooldown = 0.2)
{
	m_slash->activate(damage, getVectorToPlayer(), cooldown);
}

void MinionBehavior::decision()
{
	if (m_requested_atack)
	{
		m_requested_atack = false;
		atack(1.f, 0.2f);
		lock(0.2);
	}
	else if (MathHelper::GetLength(getVectorToPlayer()) > m_slash->getSize().x)
	{
		move();
	}
	else
	{
		m_requested_atack = true;
		lock(0.2);
	}
}
