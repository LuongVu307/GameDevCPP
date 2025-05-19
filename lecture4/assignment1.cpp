#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>


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
    virtual void customUpdate(float dt) = 0;
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

    void customUpdate(float dt) override
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

    void customUpdate(float dt) override
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

    std::vector<std::unique_ptr<CustomShape>> shapes;


    shapes.push_back(std::make_unique<Circle>(std::string("CGreen"), 50.f, sf::Vector2f(100.f, 100.f), sf::Vector2f(-3.f, 2.f), sf::Color{0, 255, 0}, font));
    shapes.push_back(std::make_unique<Circle>(std::string("CBlue"), 100.f, sf::Vector2f(200.f, 200.f), sf::Vector2f(2.f, 4.f), sf::Color{0, 0, 255}, font));
    shapes.push_back(std::make_unique<Circle>(std::string("CPurple"), 75.f, sf::Vector2f(300.f, 300.f), sf::Vector2f(-2.f, -1.f), sf::Color{0255, 0, 255}, font));
    shapes.push_back(std::make_unique<Rectangle>(std::string("RRed"), 25.f, 50.f, sf::Vector2f(300.f, 300.f), sf::Vector2f(4.f, 4.f), sf::Color{255, 0, 0}, font));
    shapes.push_back(std::make_unique<Rectangle>(std::string("RGrey"), 100.f, 50.f, sf::Vector2f(300.f, 250.f), sf::Vector2f(-2.f, 2.f), sf::Color{100, 100, 100}, font));
    shapes.push_back(std::make_unique<Rectangle>(std::string("RTeal"), 100.f, 100.f, sf::Vector2f(25.f, 100.f), sf::Vector2f(-2.f, -2.f), sf::Color{255, 255, 100}, font));
    


    window.setFramerateLimit(FPS);
    

    while (window.isOpen())
    {   
        sf::Time currentTime = clock.getElapsedTime();
        float dt = (currentTime - lastTime).asSeconds() * FPS;
        lastTime = currentTime;

        for (auto& shape : shapes) {
            shape->customUpdate(dt); 
        }


        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));

        for (auto& shape : shapes) {
            shape->draw(window); 
        }



        window.display();

    }
}
