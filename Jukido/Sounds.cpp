#include "Sounds.h"

Sounds* Sounds::ms_sounds = nullptr;

Sounds::Sounds()
{
	sf::SoundBuffer slash, shoot, cannon;
	slash.loadFromFile("sword_slash.wav");
	shoot.loadFromFile("revolver_shot.wav");
	cannon.loadFromFile("cannon_shot.wav");
	m_sounds_list = {
		{"slash", slash},
		{"shoot", shoot},
		{"cannon", cannon},};
}