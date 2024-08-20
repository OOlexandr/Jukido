#include "Enemies.h"
#include "Component.h"
#include "Behaviour.h"

Minion::Minion(sf::Texture* texture) : GameObject(texture)
{
	m_speed = 300;
}

void Minion::PostInit()
{
	m_components.push_back(new JumpComponent(this));
	m_components.push_back(new MinionBehavior(this));
}

void Minion::spawn(sf::Vector2f position)
{
	GameObject::spawn(position);
	m_health = 2;
}

Boss::Boss(const std::vector<Minion*>& minions, std::vector<sf::Vector2f> spawn_points, sf::Texture* texture) : GameObject(texture)
{
	m_minions = minions;
	m_spawn_points = spawn_points;
}

void Boss::PostInit()
{
	m_components.push_back(new JumpComponent(this));
	m_components.push_back(new BossBehavior(this, m_minions, m_spawn_points));
}

void Boss::spawn(sf::Vector2f position)
{
	GameObject::spawn(position);
	m_health = 10;
}
