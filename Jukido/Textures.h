#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "assert.h"

class Textures
{
public:
	static void createInstance()
	{
		ms_textures = new Textures();
	}

	static void destroyInstance()
	{
		delete ms_textures;
	}

	static Textures* Instance()
	{
		assert(ms_textures && "Textures were not properly loaded!");
		return ms_textures;
	}

	sf::Texture* getTexture(const std::string& texture_name)
	{
		return &m_textures_list[texture_name];
	}

public:
	Textures();

	static Textures* ms_textures;

	std::map<std::string, sf::Texture> m_textures_list;
};