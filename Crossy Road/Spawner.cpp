#include "Spawner.h"

#include <iostream>

#include "ResourceHolder.h"
#include "World.h"

//namespace
//{
//    const int MAX_INVADERS = 55;
//}
Spawner::Spawner(World& world)
    : m_stepGap(sf::seconds(0.5f))
    , m_world(world)
    , m_invaderRenderer(12, 8, Object::WIDTH, Object::HEIGHT,
        ResourceHolder::get().textures.get("si/invaders"))
{
    //Layout of the invaders 
    Object::Type types[] = {
        Object::Type::Bus, Object::Type::Car, Object::Type::Animal,
        Object::Type::tree
    };
    //Add invaders into the std::vector
    const int GAP = 10;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            //calcuate position for invader
            float invaderX = x * Object::WIDTH + (GAP * x * 3) + Object::WIDTH;
            float invaderY = y * Object::HEIGHT + (GAP * y) + Object::HEIGHT * 4;
            m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
        }
    }
}

void Spawner::tryStepInvaders()
{
    //Only step if clock is over timer
    if (m_stepTimer.getElapsedTime() > m_stepGap) {
        m_invaderRenderer.nextFrame();
        //Calculate amount to step
        bool moveDown = false;
        float step = m_isMovingLeft ? -10.0f : 10.0f;
        if (m_moveDown) {
            step *= -1;
        }


        //Move the invaders
        for (auto& invader : m_invaders) {
            if (!invader.isActive()) continue;
            invader.move(1.f);

            m_stepTimer.restart();
        }
    }
}

void Spawner::drawInvaders(sf::RenderTarget& target)
{
    for (auto& invader : m_invaders) {
        if (!invader.isActive()) continue;
        m_invaderRenderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
    }
}

    CollisionResult Spawner::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
    {
        CollisionResult result;
        std::vector<sf::Vector2f> collisionPoints;
        for (auto& projectile : projectiles) {
            for (auto& invader : m_invaders) {
                if (!invader.isActive() || !projectile.isActive())
                    continue;
                if (projectile.tryCollideWith(invader)) {
                    m_aliveInvaders--;
                    if (m_aliveInvaders == 0) {
                        m_hasAllInvadersBeenAdded = false;
                    }
                    result.second.emplace_back(invader.getPosition());
                    result.first += ((int)invader.getType() + 1) * 100;
                    updateStepDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
    {
        if (m_aliveInvaders == 0) return { -1, -1 };
        //Keep looping until an invader is found
        while (true) {
            auto invaderColumn = random.getIntInRange(0, 10);
            for (int y = 4; y >= 0; y--) {
                int index = y * 11 + invaderColumn;
                auto& invader = m_invaders.at(index);
                if (invader.isAlive()) {
                    return {
                        //transform to below the invader's center
                        invader.getPosition().x + Invader::WIDTH / 2,
                        invader.getPosition().y + Invader::HEIGHT + 5
                    };
                }
            }
        }
    }

    int InvaderManager::getAliveInvadersCount() const
    {
        return m_aliveInvaders;
    }

    //Adds invaders to scene 1 at a time
    void InvaderManager::initAddInvader()
    {
        static sf::Clock delay;
        if (delay.getElapsedTime().asSeconds() > 0.02) {
            m_invaders.at(m_initY * 11 + m_initX).makeAlive();
            m_aliveInvaders++;
            m_initX++;
            if (m_initX == 11) {
                m_initX = 0;
                m_initY--;
            }
            delay.restart();
        }

        if (m_aliveInvaders == MAX_INVADERS) {
            m_hasAllInvadersBeenAdded = true;
            m_initX = 0;
            m_initY = 4;
            updateStepDelay();
        }
    }

    bool InvaderManager::areInvadersAlive() const
    {
        return m_hasAllInvadersBeenAdded;
    }

    void InvaderManager::updateStepDelay()
    {
        m_stepGap = sf::seconds((float)m_aliveInvaders / 90.0f);
    }

    bool InvaderManager::testInvaderPosition(const Invader& invader) const
    {
        if (invader.getPosition().y > Display::HEIGHT - 150) {
            m_world.setGameIsOver();
        }
        return
            (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
            (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
    }
