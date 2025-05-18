#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class CustomShape
{
protected:
    sf::Font font;
    sf::Text text;
    std::string name;
    sf::Color color;
    sf::Vector2f velocity;
    sf::Vector2f position;

    virtual const sf::Shape& getShape() const = 0;


public:
    CustomShape(std::string name, sf::Vector2f position, 
        sf::Vector2f velocity, sf::Color color, const sf::Font& font):
        name(name),
        position(position),
        velocity(velocity),
        color(color),
        font(font),
        text(font, name, 14)
        {
        }


    virtual const sf::Text& getText() const {return text; }
    virtual void draw(sf::RenderWindow& window) const
    {
        window.draw(getShape());
        window.draw(text);
    }
    virtual ~CustomShape() = default;

    

};

class Circle final : public CustomShape
{
public: 
    Circle(std::string name, float radius, sf::Vector2f position,
           sf::Vector2f velocity, sf::Color color, const sf::Font& font)
        : CustomShape(name, position, velocity, color, font), radius(radius), shape(radius)
    {
        shape.setOrigin({radius, radius});
        shape.setPosition(position);
        shape.setFillColor(color);

        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({textRect.size.x/2, textRect.size.y});

        text.setPosition(position);
    }

    void update(float dt)
    {
        shape.move(velocity * dt);
        text.setPosition(shape.getPosition());
        bool velX_sign = velocity.x > 0, velY_sign =  velocity.y > 0;


        if ((shape.getPosition().x-radius <= 0 && velX_sign == false) ||
            (shape.getPosition().x+radius >= 1280 && velX_sign == true)
            )
        {
            velocity.x = -velocity.x;
        }
        if ((shape.getPosition().y-radius <= 0 && velY_sign == false) ||
            (shape.getPosition().y+radius >= 720 && velY_sign == true)
            )
        {
            velocity.y = -velocity.y;
        }
    }

private:
    sf::CircleShape shape;
    float radius;

    const sf::Shape& getShape() const override {return shape; }

};

class Rectangle final : public CustomShape
{
public:
    Rectangle(std::string name, float height, float width, sf::Vector2f position,
           sf::Vector2f velocity, sf::Color color, const sf::Font& font)
        : CustomShape(name, position, velocity, color, font), 
        width(width), height(height), shape({width, height})
        {
        shape.setOrigin({width/2, height/2});
        shape.setPosition(position);
        shape.setFillColor(color);

        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({textRect.size.x/2, textRect.size.y});

        text.setPosition(position);
        }

    void update(float dt)
    {
        shape.move(velocity * dt);
        text.setPosition(shape.getPosition());
        bool velX_sign = velocity.x > 0, velY_sign =  velocity.y > 0;


        if ((shape.getPosition().x-width/2 <= 0 && velX_sign == false) ||
            (shape.getPosition().x+width/2 >= 1280 && velX_sign == true)
            )
        {
            velocity.x = -velocity.x;
        }
        if ((shape.getPosition().y-height/2 <= 0 && velY_sign == false) ||
            (shape.getPosition().y+height/2 >= 720 && velY_sign == true)
            )
        {
            velocity.y = -velocity.y;
        }

    }

private:
    float width, height;
    sf::RectangleShape shape;

    const sf::Shape& getShape() const override {return shape; }

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

    Rectangle RRed("RRed", 25, 50, {300, 300}, {4, 4}, sf::Color{255, 0, 0}, font);
    Rectangle RGrey("RGrey", 100, 50, {300, 250}, {-2, 2}, sf::Color{100, 100, 100}, font);
    Rectangle RTeal("RTeal", 100, 100, {25, 100}, {-2, -2}, sf::Color{255, 255, 100}, font);


    window.setFramerateLimit(FPS);
    

    while (window.isOpen())
    {   
        sf::Time currentTime = clock.getElapsedTime();
        float dt = (currentTime - lastTime).asSeconds() * FPS;
        lastTime = currentTime;

        CGreen.update(dt);
        CBlue.update(dt);
        CPurple.update(dt);
        RRed.update(dt);
        RGrey.update(dt);
        RTeal.update(dt);


        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));

        CGreen.draw(window);
        CBlue.draw(window);
        CPurple.draw(window);
        RRed.draw(window);
        RGrey.draw(window);
        RTeal.draw(window);



        window.display();

    }
}
