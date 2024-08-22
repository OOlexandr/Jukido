#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "GameStateManager.h"
#include "WindowHelper.h"
#include "GameWorld.h"
#include "Textures.h"
#include "Sounds.h"

void handleSystemEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Key::Escape)
                window.close();
        default:
            break;
        }
    }
}

int main()
{
    srand(time(0));

    sf::RenderWindow& window = WindowHelper::Instance().GetRenderWindow();

    Textures::createInstance();
    Sounds::createInstance();

    GameWorld::createInstance(&window);
    GameWorld::Instance()->PostInit();

    GameWorld* gameWorld = GameWorld::Instance();
    GameStateManager gameStateManager(gameWorld, GameStateId::Playing);

    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        handleSystemEvents(window);

        gameStateManager.getCurrentGameState()->update(deltaTime);
        gameStateManager.getCurrentGameState()->draw(&window);
        gameStateManager.getCurrentGameState()->updateState();

        window.display();
    }

    GameWorld::destroyInstance();
    Textures::destroyInstance();
    Sounds::destroyInstance();

    return 0;
}