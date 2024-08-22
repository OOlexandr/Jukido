#include "Component.h"
#include "GameObjects.h"
#include "Player.h"
#include "MathHelper.h"
#include "Textures.h"

JumpComponent::JumpComponent(GameObject* object) : m_owner(object)
{
    m_buffer.loadFromFile("jump.wav");
    m_jumpSound.setBuffer(m_buffer);
}


void JumpComponent::update(float dt)
{
    //Update velocity
    if (jumpRequested())
    {
        //apply velocity UP
        const float jumpImpulseValue = -1000.0f;
        m_owner->updateSpeedY(jumpImpulseValue);

        m_jumpSound.play();
    }
    else
    {
        //apply gravity DOWN
        const float acceleration = 2000.0f;
        const float terminal_velocity = 2000.0f; // should reach terminal velocity in 1.5 seconds after a jump
        const float delta_velocity = std::min(acceleration * dt, terminal_velocity);
        const sf::Vector2f velocity = m_owner->getCurrentSpeed();
        if (m_owner->isOnTheGround())
        {
            m_owner->updateSpeedY(std::min(0.0f, velocity.y + delta_velocity));// forbids moving down when on the ground
        }
        else
        {
            m_owner->updateSpeedY(velocity.y + delta_velocity);
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
        if (!m_jumpPressedLastFrame && m_owner->isOnTheGround())
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
    for (size_t i = 0; i < 6; i++)
    {
        m_bullets.push_back(new Bullet(Textures::Instance()->getTexture("bullet"), player));
    }
    m_slashes.push_back(new Slash(Textures::Instance()->getTexture("slash_player0"), player));
    m_slashes.push_back(new Slash(Textures::Instance()->getTexture("slash_player1"), player));
    m_slashes.push_back(new Slash(Textures::Instance()->getTexture("slash_player2"), player));
}

PlayerAtackComponent::~PlayerAtackComponent()
{
    for (Projectile* p : m_slashes)
    {
        delete p;
    }
    for (Projectile* p : m_bullets)
    {
        delete p;
    }
}

void PlayerAtackComponent::update(float dt)
{
    m_cooldown = std::max(m_cooldown - dt, 0.f);

    if (m_player->isOnTheGround())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!m_atackPressedLastFrame && !m_requested_atack)
            {
                m_requested_atack = true;
                m_combo += 1;
            }
            
            m_atackPressedLastFrame = true;
        }
        else
        {
            m_atackPressedLastFrame = false;
        }

        if (m_requested_atack && m_cooldown <= 0.0f)
        {
            m_requested_atack = false;
            m_cooldown = 0.3f;
            atackSword();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (!m_shootPressedLastFrame && m_player->getRounds() >= 1)
            {
                m_requested_shoot = true;
            }
            m_shootPressedLastFrame = true;
        }
        else
        {
            m_shootPressedLastFrame = false;
        }

        if (m_requested_shoot && m_cooldown <= 0.0f)
        {
            m_requested_shoot = false;
            fire();
            m_player->decreaseRounds();
            // no cooldown on firing.
            // The limit to firearm's dps is not fire rate but capacity.
            // But shooting in the middle of a slash is not allowed.
        }
    }

    if (m_cooldown <= 0)
    {
        m_combo = 0;
    }

    for (Projectile* p : m_slashes)
    {
        if (p->isActive())
        {
            p->update(dt);
        }
    }
    for (Projectile* p : m_bullets)
    {
        if (p->isActive())
        {
            p->update(dt);
        }
    }
}

void PlayerAtackComponent::draw(sf::RenderWindow* window)
{
    for (Projectile* p : m_slashes)
    {
        if (p->isActive())
        {
            p->draw(window);
        }
    }
    for (Projectile* p : m_bullets)
    {
        if (p->isActive())
        {
            p->draw(window);
        }
    }
}

void PlayerAtackComponent::atackSword()
{
    if (m_combo <= m_slashes.size())
    {
        m_slashes[m_combo-1]->activate(1, (sf::Vector2f(sf::Mouse::getPosition()) - m_player->getPosition()), 0.3);
    }
    else
    {
        m_combo = 0;
    }
}

void PlayerAtackComponent::fire()
{
    for (Projectile* p : m_bullets)
    {
        if (!p->isActive())
        {
            p->activate(1, (sf::Vector2f(sf::Mouse::getPosition()) - m_player->getPosition()), 0.4);
            break;
        }
    }
}
