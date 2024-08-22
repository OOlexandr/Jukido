#include "Behaviour.h"
#include "GameWorld.h"
#include "MathHelper.h"
#include "Enemies.h"
#include "Textures.h"
#include "Sounds.h"

Behavior::~Behavior()
{
	for (Projectile* p : m_projectiles)
	{
		delete p;
	}
}

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

void Behavior::despawn()
{
	m_locked = false;
	m_cooldown = 0;
	for (Projectile* p : m_projectiles)
	{
		p->despawn();
	}
}

MinionBehavior::MinionBehavior(GameObject* owner) : Behavior(owner)
{
	m_slash = new Slash(Textures::Instance()->getTexture("slash_enemy"), m_owner);
	m_projectiles.push_back(m_slash);
	m_slash_sound.setBuffer(*Sounds::Instance()->getSound("slash"));
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
	m_slash_sound.play();
}

void MinionBehavior::decision()
{
	if (m_requested_atack)
	{
		m_requested_atack = false;
		atack(1.f, 0.3f);
		lock(0.3);
	}
	else if (MathHelper::GetLength(getVectorToPlayer()) > m_slash->getSize().x)
	{
		move();
	}
	else
	{
		m_requested_atack = true;
		lock(0.3);
	}
}

BossBehavior::BossBehavior(GameObject* owner, const std::vector<Minion*>& minions, std::vector<sf::Vector2f> spawn_points
							, std::vector<sf::Vector2f> cannon_points) : Behavior(owner)
{
	m_minions = minions;
	m_spawn_points = spawn_points;
	m_cannon_points = cannon_points;
	m_cannonball1 = new CannonBall(Textures::Instance()->getTexture("cannonball"), Textures::Instance()->getTexture("target"), m_owner);
	m_cannonball2 = new CannonBall(Textures::Instance()->getTexture("cannonball"), Textures::Instance()->getTexture("target"), m_owner);
	m_projectiles.push_back(m_cannonball1);
	m_projectiles.push_back(m_cannonball2);
	m_cannon_sound.setBuffer(*Sounds::Instance()->getSound("cannon"));
}

void BossBehavior::decision()
{
	if (!getNumberOfActiveMinions())
	{
		spawnMinions();
		lock(3);
	}
	else
	{
		fireCannons();
		lock(3);
	}
}

int BossBehavior::getNumberOfActiveMinions()
{
	int num = 0;
	for (Minion* m : m_minions)
	{
		if (m->isActive())
		{
			num++;
		}
	}
	return num;
}

void BossBehavior::spawnMinions()
{
	for (size_t i = 0; i < m_minions.size(); i++)
	{
		m_minions[i]->spawn(m_spawn_points[i]);
	}
}

void BossBehavior::fireCannons()
{
	sf::Vector2f cannon1 = m_cannon_points[rand() % m_cannon_points.size()];
	sf::Vector2f cannon2 = m_cannon_points[rand() % m_cannon_points.size()];
	while (cannon1 == cannon2)
	{
		cannon2 = m_cannon_points[rand() % m_cannon_points.size()];
	}

	m_cannonball1->activate(1, cannon1, 2);
	m_cannonball2->activate(1, cannon2, 2);

	m_cannon_sound.play();
}