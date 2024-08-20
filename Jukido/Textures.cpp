#include "Textures.h"

Textures* Textures::ms_textures = nullptr;

Textures::Textures()
{
	sf::Texture minion, player, boss, bullet, slash_player, slash_enemy;
	minion.loadFromFile("BOX.png");
	boss.loadFromFile("stone.png");
	player.loadFromFile("MINECRAFT_SPRITE.png");
	bullet.loadFromFile("ball2.png");
	slash_player.loadFromFile("HorizontalSlash2.png");
	slash_enemy.loadFromFile("RedSlash2.png");
	m_textures_list = {
		{"minion", minion},
		{"player", player},
		{"boss", boss},
		{"bullet", bullet},
		{"slash_player", slash_player},
		{"slash_enemy", slash_enemy} };
}