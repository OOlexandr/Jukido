#pragma once
#include "GameObjects.h"

class Projectile : public GameObject
{
public:
	Projectile(sf::Texture* texture, GameObject* owner);
	void update(float deltaTime) override;
	virtual void DealDamage(GameObject* target);
	virtual void activate(float damage, sf::Vector2f direction, float longevity);
	void deactivate();
	void despawn() override;

protected:
	float m_damage = 0;
	float m_time_alive = 0;
	float m_longevity = 0;
	GameObject* m_owner = nullptr; // to avoid self damage
};

class Slash : public Projectile
{
public:
	Slash(sf::Texture* texture, GameObject* owner);

	void activate(float damage, sf::Vector2f direction, float longevity);

	void update(float deltaTime) override;

	void DealDamage(GameObject* target) override;

private:
	std::vector<GameObject*> m_hit_targets;
};

class Bullet : public Projectile
{
public:
	Bullet(sf::Texture* texture, GameObject* owner) : Projectile(texture, owner) {}

	void updatePosition(float dt) override;

	void activate(float damage, sf::Vector2f direction, float longevity);

	void update(float deltaTime) override;

protected:
	float m_speed = 5000.f;
};