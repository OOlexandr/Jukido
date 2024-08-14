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
        const float jumpImpulseValue = -1500.0f;
        m_velocity.y = jumpImpulseValue;

        m_jumpSound.play();
    }
    else
    {
        //apply gravity DOWN
        //will constantly speedup even when standing on the ground. Needs fixing.
        const float acceleration = 9.8f;
        const float terminal_velocity = 30.0f; // not too much.
        m_velocity.y += acceleration * dt;
    }

    //calculate new position applying velocity
    //s = v * t
    const sf::Vector2f displacement{ m_velocity.x * dt, m_velocity.y * dt };
    const sf::Vector2f oldPosition = m_player->getSprite()->getPosition();
    m_player->getSprite()->setPosition(oldPosition + displacement);
}

bool PlayerJumpComponent::jumpRequested()
{
    bool requestJump = false;
    bool isJumpPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        isJumpPressed = true;
        if (!m_jumpPressedLastFrame)
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
        m_referenceObject->updatePosition({ NormalizedDirection.x * DeltaSpeed, NormalizedDirection.y * DeltaSpeed });
    }
}
