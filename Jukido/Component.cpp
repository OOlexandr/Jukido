#include "Component.h"
#include "GameObjects.h"
#include "Player.h"
#include "MathHelper.h"

PlayerJumpComponent::PlayerJumpComponent(Player* player) : m_player(player)
{
    m_buffer.loadFromFile("jump.wav");
    m_jumpSound.setBuffer(m_buffer);
}


void PlayerJumpComponent::update(float dt)
{
    //Update velocity
    if (jumpRequested())
    {
        //apply velocity UP
        const float jumpImpulseValue = -1000.0f;
        m_player->updateSpeedY(jumpImpulseValue);

        m_jumpSound.play();
    }
    else
    {
        //apply gravity DOWN
        const float acceleration = 2000.0f;
        const float terminal_velocity = 2000.0f; // should reach terminal velocity in 1.5 seconds after a jump
        const float delta_velocity = std::min(acceleration * dt, terminal_velocity);
        const sf::Vector2f velocity = m_player->getCurrentSpeed();
        if (m_player->isOnTheGround())
        {
            m_player->updateSpeedY(std::min(0.0f, velocity.y + delta_velocity));// forbids moving down when on the ground
        }
        else
        {
            m_player->updateSpeedY(velocity.y + delta_velocity);
        }
    }

    //calculate new position applying velocity
    //s = v * t
    //const sf::Vector2f displacement{ m_velocity.x * dt, m_velocity.y * dt };
    //const sf::Vector2f oldPosition = m_player->getSprite()->getPosition();
    //m_player->updatePosition(displacement);
}

bool PlayerJumpComponent::jumpRequested()
{
    bool requestJump = false;
    bool isJumpPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        isJumpPressed = true;
        if (!m_jumpPressedLastFrame && m_player->isOnTheGround())
        {
            requestJump = true;
        }
    }
    m_jumpPressedLastFrame = isJumpPressed;

    return requestJump;
}

ShowObjectOriginComponent::ShowObjectOriginComponent(GameObject* gameObject) : m_gameObject(gameObject), m_circle(5, 10)
{
    m_circle.setFillColor(sf::Color::Blue);
    m_circle.setOrigin(m_circle.getGlobalBounds().getSize().x, m_circle.getGlobalBounds().getSize().y);
}

void ShowObjectOriginComponent::update(float dt)
{
    m_circle.setPosition(m_gameObject->getPosition());
}

void ShowObjectOriginComponent::draw(sf::RenderWindow* window)
{
    window->draw(m_circle);
}



void AIMoveStraightLineComponent::update(float dt)
{
    moveTo(dt, m_targetObject->getPosition());
}

AIMoveToComponent::AIMoveToComponent(GameObject* referenceObject, GameObject* targetObject)
    : m_referenceObject(referenceObject), m_targetObject(targetObject)
{
}

void AIMoveToComponent::moveTo(float dt, const sf::Vector2f& position)
{
    const float DeltaSpeed = dt * m_speed;

    const sf::Vector2f Direction = position - m_referenceObject->getPosition();
    if (MathHelper::GetLength(Direction) > m_minimalDistance)
    {
        const sf::Vector2f NormalizedDirection = MathHelper::Normalize(Direction);
        //m_referenceObject->updatePosition({ NormalizedDirection.x * DeltaSpeed, NormalizedDirection.y * DeltaSpeed });
    }
}

void PlayerMovementComponent::update(float dt)
{
    const float MoveDelta = m_player->getSpeed();

    float deltaX = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        deltaX += MoveDelta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        deltaX -= MoveDelta;
    }
    m_player->updateSpeedX(deltaX);
}

PlayerAtackComponent::PlayerAtackComponent(Player* player) : m_player(player)
{
    m_sword_slash = new Slash("HorizontalSlash2.png", player);
}

void PlayerAtackComponent::update(float dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_player->isOnTheGround())
        {
            m_sword_slash->activate(m_player->getPosition(), 1, (sf::Vector2f(sf::Mouse::getPosition()) - m_player->getPosition()), 0.2);
        }
    }

    if (m_sword_slash->isActive())
    {
        m_sword_slash->update(dt);
    }
}

void PlayerAtackComponent::draw(sf::RenderWindow* window)
{
    m_sword_slash->draw(window);
}
