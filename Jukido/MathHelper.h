#pragma once
#include <SFML/Window.hpp>

class MathHelper
{
public:
	static float GetLength(const sf::Vector2f& vec)
	{
		return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	}

	static sf::Vector2f Normalize(const sf::Vector2f& vec)
	{
		const float len = GetLength(vec);
		return { vec.x / len, vec.y / len };
	}
};