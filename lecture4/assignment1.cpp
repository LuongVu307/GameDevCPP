#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <imgui.h>
#include <imgui-SFML.h>


class CustomShape
{
protected:
    sf::Font font;
    sf::Text text;
    std::string name;
    sf::Color color;
    sf::Vector2f velocity;
    sf::Vector2f position;
    bool drawing;
    std::string type;

    virtual const sf::Shape& getShape() const = 0;



public:
    CustomShape(std::string name, sf::Vector2f position, 
        sf::Vector2f velocity, sf::Color color, const sf::Font& font):
        name(name),
        position(position),
        velocity(velocity),
        color(color),
        font(font),
        text(font, name, 14),
        drawing(true)
        {
        }

    virtual ~CustomShape() = default;

    virtual void customUpdate(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const
    {
        window.draw(getShape());
        window.draw(text);
    }

    const std::string& getName() const {return name; }
    const sf::Vector2f& getVelocity() const {return velocity; }
    const sf::Color& getColor() const {return color; }
    const bool& getDrawing() const {return drawing; }
    virtual const std::vector<float> getSize() = 0;
    const std::string& getType() const {return type; }
 
    void setVelocity(sf::Vector2f newVelocity) {velocity = newVelocity;}
    void setDrawing(bool value) {drawing = value; }
    void setColor(sf::Color newColor) {color = newColor; }
    virtual void setSize(std::vector<float>& size) = 0;
    void setName(const std::string& newName) 
    {
        name = newName;
        text.setString(name);
    }
    

};

class Circle final : public CustomShape
{
public: 
    Circle(std::string name, float radius, sf::Vector2f position,
           sf::Vector2f velocity, sf::Color color, const sf::Font& font)
        : CustomShape(name, position, velocity, color, font), radius(radius), shape(radius)
    {
        type = "Circle";
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
        shape.setFillColor(color);
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

    const std::vector<float> getSize() override
    {
        return { radius };
    }

    void setSize(std::vector<float>& newRadius) override 
    {
        radius = newRadius[0];
        shape.setRadius(radius);
        shape.setOrigin({radius, radius});

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
        type = "Rectangle";
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
        shape.setFillColor(color);
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

    const std::vector<float> getSize() override
    {
        return { width, height };
    }

    void setSize(std::vector<float>& newSize) override 
    {
        width = newSize[0];
        height = newSize[1];
        shape.setSize(sf::Vector2f{width, height});
        shape.setOrigin({width/2, height/2});
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
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;


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

        while (auto event = window.pollEvent()) {

            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Debug Panel");
        ImGui::Text("Parameters of Shapes");
    
        static int current_item = 0;

        static std::vector<std::string> shapeNames= {};
        std::vector<const char*> itemPtrs;

        shapeNames.clear();
        itemPtrs.clear();

        for (const auto& shape : shapes)
        {
            shapeNames.push_back(shape->getName());
            itemPtrs.push_back(shapeNames.back().c_str());
        }        

        if (ImGui::Combo("Shapes", &current_item, itemPtrs.data(), static_cast<int>(itemPtrs.size())))
        {
            // std::cout << "Selected Shape: " << shapeNames[current_item] << std::endl;
        }

        auto& selectedShape = shapes[current_item];


        bool drawing = selectedShape->getDrawing();
        std::string checkboxLabel = std::format("Drawing {}", selectedShape->getName());
        if (ImGui::Checkbox(checkboxLabel.c_str(), &drawing))
        {
            selectedShape->setDrawing(drawing);
        }


        sf::Vector2f velocity = selectedShape->getVelocity();
        if (ImGui::SliderFloat2("Velocity", &velocity.x, -6.f, 6.f))
        {
            selectedShape->setVelocity(velocity);
        }

        sf::Color color = selectedShape->getColor();
        int colorInt[3] = { static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b) };

        if (ImGui::SliderInt3("Color", colorInt, 0, 255))
        {
            color.r = static_cast<std::uint8_t>(colorInt[0]);
            color.g = static_cast<std::uint8_t>(colorInt[1]);
            color.b = static_cast<std::uint8_t>(colorInt[2]);

            selectedShape->setColor(color);
        }


        if (selectedShape->getType() == "Circle")
        {
            float radius = selectedShape->getSize()[0];
            if (ImGui::SliderFloat("Radius", &radius, 10.f, 200.f))
            {
                std::vector<float> newRadius = {radius};
                selectedShape->setSize(newRadius);
            }
        } 
        else if (selectedShape->getType() == "Rectangle")
        {
            std::vector<float> size = selectedShape->getSize();
            if (ImGui::SliderFloat2("Size", &size[0], 10.f, 200.f))
            {
                selectedShape->setSize(size);
            }

        }


        static char nameBuffer[64];
        std::string currentName = selectedShape->getName();
        std::strncpy(nameBuffer, currentName.c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0'; 

        if (ImGui::InputText("Name", nameBuffer, IM_ARRAYSIZE(nameBuffer))) 
        {
            selectedShape->setName(nameBuffer);
        }   

        
        ImGui::End();


        window.clear(sf::Color(0, 0, 0));
        for (auto& shape : shapes) {
            if (shape->getDrawing() == true)
            {
                shape->draw(window); 
            }
            
        }
        ImGui::SFML::Render(window);

        window.display();

    }
}
