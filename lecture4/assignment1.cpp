#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Circle
{
    sf::CircleShape circle;
    std::string name;
    sf::Color color;
    sf::Vector2f velocity;
    const sf::Font& font;
    sf::Text text;
    float radius;

public: 
    Circle(std::string name, float radius, sf::Vector2f position, 
        sf::Vector2f velocity, sf::Color color, sf::Font& font) :
        name(name), radius(radius),
        velocity(velocity),
        color(color),
        font(font),
        text(font, name, 18)
    {
        circle.setPosition(position);
        circle.setFillColor(color);
        circle.setOrigin({radius, radius});
        circle.setRadius(radius);

        text.setFillColor(sf::Color::White);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({textRect.size.x/2, textRect.size.y});
    }

    void update(float dt)
    {
        circle.move(velocity * dt);
        text.setPosition(circle.getPosition());
        bool velX_sign = velocity.x > 0, velY_sign =  velocity.y > 0;


        if ((circle.getPosition().x-radius <= 0 && velX_sign == false) ||
            (circle.getPosition().x+radius >= 1280 && velX_sign == true)
            )
        {
            velocity.x = -velocity.x;
        }
        if ((circle.getPosition().y-radius <= 0 && velY_sign == false) ||
            (circle.getPosition().y+radius >= 720 && velY_sign == true)
            )
        {
            velocity.y = -velocity.y;
        }
    }

    const sf::CircleShape& getCircle() const {return circle; }
    const sf::Text& getText() const {return text; }

};



int main(int argc, char * argv[])
{
    unsigned int _WIDTH = 1280, _HEIGHT = 720;
    unsigned int FPS = 120;

    sf::Clock clock;
    sf::Time lastTime = clock.getElapsedTime();

    sf::Font font;
    if (!font.openFromFile("tech.ttf"))
    {
        std::cout << "Cannot find font 'tech.ttf' \n";
        return 1;
    }


    sf::RenderWindow window(sf::VideoMode({_WIDTH, _HEIGHT}), "Assignment 1");

    Circle CGreen("CGreen", 50., {100., 100.}, {-3., 2.}, sf::Color{0, 255, 0}, font);
    Circle CBlue("CBlue", 100., {200., 200.}, {2., 4.}, sf::Color{0, 0, 255}, font);
    Circle CPurple("CPurple", 75., {300., 300.}, {-2., -1.}, sf::Color{255, 0, 255}, font);
    

    window.setFramerateLimit(FPS);
    

    while (window.isOpen())
    {   
        sf::Time currentTime = clock.getElapsedTime();
        float dt = (currentTime - lastTime).asSeconds() * FPS;
        lastTime = currentTime;

        CGreen.update(dt);
        CBlue.update(dt);
        CPurple.update(dt);

        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));

        window.draw(CGreen.getCircle());
        window.draw(CBlue.getCircle());
        window.draw(CPurple.getCircle());

        window.draw(CGreen.getText());
        window.draw(CBlue.getText());
        window.draw(CPurple.getText());


        window.display();

    }
}
