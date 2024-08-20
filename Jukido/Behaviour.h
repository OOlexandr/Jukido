// Both "behaviour" and "behavior" are correct.

#pragma once
#include "Component.h"

class Minion;

class Behavior : public Component
{
public:
	Behavior(GameObject* owner) : m_owner(owner) {}

	sf::Vector2f getVectorToPlayer();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	virtual void decision() {}
	void lock(float time);
	void despawn() override;

protected:
	GameObject* m_owner;
	std::vector<Projectile*> m_projectiles;
	bool m_locked = false;
	float m_cooldown = 0;
	bool m_requested_atack = false;
};

class MinionBehavior : public Behavior
{
public:
	MinionBehavior(GameObject* owner);
	void move();
	void atack(float damage, float cooldown);
	void decision() override;

protected:
	Slash* m_slash = nullptr;
};

class BossBehavior : public Behavior
{
public:
	BossBehavior(GameObject* owner, const std::vector<Minion*>& minions, std::vector<sf::Vector2f> spawn_points);
	void decision() override;
	int getNumberOfActiveMinions();
	void spawnMinions();

protected:
	std::vector<Minion*> m_minions;
	std::vector<sf::Vector2f> m_spawn_points;
};