#pragma once
#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "assert.h"

class Sounds
{
public:
	static void createInstance()
	{
		ms_sounds = new Sounds();
	}

	static void destroyInstance()
	{
		delete ms_sounds;
	}

	static Sounds* Instance()
	{
		assert(ms_sounds && "Sounds were not properly loaded!");
		return ms_sounds;
	}

	sf::SoundBuffer* getSound(const std::string& sound_name)
	{
		return &m_sounds_list[sound_name];
	}

public:
	Sounds();

	static Sounds* ms_sounds;

	std::map<std::string, sf::SoundBuffer> m_sounds_list;
};