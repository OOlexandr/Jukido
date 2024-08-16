#pragma once
#include "GameObjects.h"

class Projectile : public GameObject
{
public:
	Projectile(const char* textureFileName, const GameObject* owner);
	void update(float deltaTime) override;
	void DealDamage(GameObject* target);
	virtual void activate(sf::Vector2f position, float damage, sf::Vector2f direction, float longevity);
	void deactivate();
	bool isActive() { return m_active; }

protected:
	float m_damage = 0;
	float m_time_alive = 0;
	float m_longevity = 0;
	const GameObject* m_owner = nullptr; // to avoid self damage
	bool m_active = false;
};

class Slash : public Projectile
{
public:
	Slash(const char* textureFileName, const GameObject* owner) : Projectile(textureFileName, owner) {}

	void activate(sf::Vector2f position, float damage, sf::Vector2f direction, float longevity);

	void update(float deltaTime) override;
};