#include "Game.h"

#include <iostream>

Game::Game(const std::string & config)
{
    init(config);
};

void Game::init(const std::string& config)
{
    // TODO: read in config file here
    //       use the premade PlayerConfig, EnemyCOnfig, BulletConfig

    //set up detault window parameters
    m_window.create(sf::VideoMode({1280, 720}), "Assignment2");
    m_window.setFramerateLimit(60);

    ImGui::SFML::Init(m_window);

    // scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    spawnPlayer();
}

std::shared_ptr<Entity> Game::player()
{
    auto& players = m_entities.getEntities("player");
    
    assert(players.size() == 1);

    return players.front();
}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems shoud function while paused (rendering, ...)
    //       some systems shouldn't (movement / input)

    while (m_running)
    {
        //Update the entity manager
        m_entities.update();

        //required update call to imgui
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sGUi();
        sRender();
        
        //increment the current frame
        m_currentFrame++;
    }
}

void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config

    // We create every entity by calling EntityManager.addEntity(tag)
    // This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
    auto entity = m_entities.addEntity("player");

    // Give this entity a Transform so it spawns at (200, 200) with velocity (1, 1) and angle 0
    entity->add<CTransform>(Vec2f(200.f, 200.f), Vec2f(1.0f, 1.0f), 0.0f);

    // The entity's shape will have radius 32, 8 sidesm darkgrey fill, and red outline of thickness 4
    entity->add<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

    // Add an input componenet to the player
    entity->add<CInput>();
}

void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //       the enemy must be spawned completely within the bounds of the window

    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO: spawn small enemies at the location of the enemy
            //  - spawn a number of small enemies equal tothe verticies of the original one
            //  - set each small enemy to the same color as the original, half the size
            //  - small enemies are worth double points of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& Target)
{
    // TODO: Implement the spawning of a bullet which travels toward target
    //       - bullet speed is given as a scalar speed
    //       - must set velocity by using formula
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO :D
}

void Game::sMovement()
{
    // TODO: implement all eneity move ment in this function
    //       should read the m_player->cInput component to determine if the player is moving

    auto& transform = player()->get<CTransform>();
    transform.pos.x += transform.velocity.x;
    transform.pos.y += transform.velocity.y;
}

void Game::sLifespan()
{
    // TODO: implement all lifespan functionality
    //       - for all enemies
    //           + if entity has no lifespan component, skip
    //           + if entity has > 0 remaining lifespan, -= 1
    //           + if it has lifespan and is alive --> scale its alpha channel properly
    //           + if it has a lifespan and its time is up --> destroy entity
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities, using collision radius, not shape radius
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
}

void Game::sGUi()
{
    ImGui::Begin("Geometry Wars");

    ImGui::Text("Stuff Goes Here");

    ImGui::End();
}

void Game::sRender()
{
    // TOOD: change the code below to draw ALL of the entities
    //       sample drawing of the player Entity that we have created
    m_window.clear();

    // set the positio nfo the shape based on the entities transform->pos
    player()->get<CShape>().circle.setPosition(player()->get<CTransform>().pos);

    // set the rotation of the shape based on the entity's transform->angle
    player()->get<CTransform>().angle += sf::degrees(1.0f);
    player()->get<CShape>().circle.setRotation(player()->get<CTransform>().angle);

    //draw the entity's sf::CircleShape
    m_window.draw(player()->get<CShape>().circle);

    // draw the ui last
    ImGui::SFML::Render(m_window);
    
    m_window.display();
}

void Game::sUserInput()
{
    //TODO: handle user input here
            // should only set player's input componenet variable here
            // should not implement the player's movement logic here
            // movement system will read the variables set in this function
    
    while (auto event = m_window.pollEvent())
    {
        //pass the event to imgui to be parsed
        ImGui::SFML::ProcessEvent(m_window, *event);

        //this event triggers when the window is closed
        if (event->is<sf::Event::Closed>())
        {
            m_running = false;
        }

        if (event->is<sf::Event::KeyReleased>())
        {
            auto key = event->getIf<sf::Event::KeyReleased>();
            switch (static_cast<char>(key->code))
            {
                case 'w':
                    std::cout << "W key Released\n";
                    //TODOL set player's input component "up" to false
                    break;
                case 'd':
                    std::cout << "d key Released\n";
                    //TODOL set player's input component "right" to false
                    break;
                case 's':
                    std::cout << "skey Released\n";
                    //TODOL set player's input component "down" to false
                    break;
                case 'a':
                    std::cout << "a key Released\n";
                    //TODOL set player's input component "left" to false
                    break;
                

                default: break;
            }
        }

        if (event->is<sf::Event::KeyPressed>())
        {
            auto key = event->getIf<sf::Event::KeyPressed>();
            switch (static_cast<char>(key->code))
            {
                case 'w':
                    std::cout << "W key Released\n";
                    //TODOL set player's input component "up" to true
                    break;
                case 'd':
                    std::cout << "d key Released\n";
                    //TODOL set player's input component "right" to true
                    break;
                case 's':
                    std::cout << "skey Released\n";
                    //TODOL set player's input component "down" to true
                    break;
                case 'a':
                    std::cout << "a key Released\n";
                    //TODOL set player's input component "left" to true
                    break;
                

                default: break;
            }
        }

        if (event->is<sf::Event::MouseButtonPressed>())
        {
            if (ImGui::GetIO().WantCaptureMouse) { continue; }
            
            auto key = event->getIf<sf::Event::MouseButtonPressed>();
            switch (static_cast<int>(key->button))
            {
                case 0:
                    // TODO
                    std::cout << "Left mouse Button clicked at (" << key->position.x << ", " << key->position.y << ")\n" ;
                    break;
                
                case 1:

                    //TODO
                    std::cout << "Left mouse Button clicked at (" << key->position.x << ", " << key->position.y << ")\n" ;
                    break;

                default: break;
            }
        }


    }
}

