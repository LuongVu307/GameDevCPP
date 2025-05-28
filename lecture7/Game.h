#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.hpp"
#include "EntityManager.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L, SB; float S; };


class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text = sf::Text(m_font, "", 0);
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    sf::Clock m_deltaClock;
    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false; // whether we update game logic
    bool m_running = true; // whether the game is running

    void init(const std::string & config); //initialize the GameState with a config file
    void setPaused(bool paused); //pause the game

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sGUi();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    std::shared_ptr<Entity> player();

public:

    Game(const std::string & config);

    void run();
};