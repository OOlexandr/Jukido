#pragma once
#include <SFML/Graphics.hpp>

class WindowHelper
{
public:
	WindowHelper() : m_window(sf::VideoMode::getDesktopMode(), "Jukido"/*, sf::Style::Fullscreen*/)
	{
	}

	static WindowHelper& Instance()
	{
		static WindowHelper window;
		return window;
	}

	sf::RenderWindow& GetRenderWindow() { return m_window; }

	sf::RenderWindow m_window;
};