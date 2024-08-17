// Both "behaviour" and "behavior" are correct.

#pragma once
#include "Component.h"

class Behavior : public Component
{
public:
	Behavior(GameObject* owner) : m_owner(owner) {}

	sf::Vector2f getVectorToPlayer();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
	virtual void decision() {}
	void lock(float time);

protected:
	GameObject* m_owner;
	std::vector<Projectile*> m_projectiles;
	bool m_locked = true;
	float m_cooldown = 5;
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

class BossBehavior :