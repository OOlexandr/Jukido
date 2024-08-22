#include "Textures.h"

Textures* Textures::ms_textures = nullptr;

Textures::Textures()
{
	sf::Texture minion, player, boss, bullet, slash_player0, slash_player1, slash_player2, slash_enemy;
	minion.loadFromFile("BOX.png");
	boss.loadFromFile("stone.png");
	player.loadFromFile("MINECRAFT_SPRITE.png");
	bullet.loadFromFile("ball2.png");
	slash_player0.loadFromFile("PlayerSlash0.png");
	slash_player1.loadFromFile("PlayerSlash1.png");
	slash_player2.loadFromFile("PlayerSlash2.png");
	slash_enemy.loadFromFile("RedSlash2.png");
	m_textures_list = {
		{"minion", minion},
		{"player", player},
		{"boss", boss},
		{"bullet", bullet},
		{"slash_player0", slash_player0},
		{"slash_player1", slash_player1},
		{"slash_player2", slash_player2},
		{"slash_enemy", slash_enemy} };
}