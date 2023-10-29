#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>

class graphic {

public:
    double a;
    double b;
    double c;
    bool iscreated = false;

    sf::VertexArray x_axis;
    sf::VertexArray y_axis;
    sf::VertexArray quadratic;

    void createparabola() {
        quadratic = sf::VertexArray(sf::LineStrip, 200);
        for (int i = 0; i < 200; i++)
        {
            double x = i - 100;
            double y = a * x * x + b * x + c;
            quadratic[i].position = sf::Vector2f(x + 300, -y + 300);
            quadratic[i].color = sf::Color::Green;
            iscreated = true;
        }

    }

    void creategraphic() {
        x_axis = sf::VertexArray(sf::Lines, 2);
        
        x_axis[0].position = sf::Vector2f(50, 300);
        x_axis[1].position = sf::Vector2f(550, 300);
        x_axis[0].color = sf::Color::Black;
        x_axis[1].color = sf::Color::Black;

        y_axis = sf::VertexArray(sf::Lines, 2);
        y_axis[0].position = sf::Vector2f(300, 0);
        y_axis[1].position = sf::Vector2f(300, 580);
        y_axis[0].color = sf::Color::Black;
        y_axis[1].color = sf::Color::Black;
    }
     

};

class inputfield {
public:
    std::string str;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape inputBox;
    bool isSelected = false;

    void createInputField(sf::Vector2f position, sf::Vector2f size) {
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position);

        inputBox.setSize(size);
        inputBox.setPosition(position);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineColor(sf::Color::Black);
        inputBox.setOutlineThickness(1);
    }

    void handleInput(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);

                if (inputBox.getGlobalBounds().contains(mousePosition)) {
                    isSelected = true;
                }
                else {
                    isSelected = false;
                }
            }
        }
        else if (event.type == sf::Event::TextEntered && isSelected) {
            if (event.text.unicode == 8 && !text.getString().isEmpty()) {
                
                str = str.substr(0, str.size() - 1);
                text.setString(str);
            }
            else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                str = text.getString();
                str += static_cast<char>(event.text.unicode);
                text.setString(str);
            }
        }
    }

    void update() {
        if (isSelected) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                isSelected = false;
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(inputBox);
        window.draw(text);
    }
};

class Button {
public:
    sf::RectangleShape button;

    void CreateButton() {
        button.setPosition(sf::Vector2f(750, 500));
        button.setFillColor(sf::Color(0, 255, 0));
        button.setSize(sf::Vector2f(200, 40));
    }
    
 

};


int main()
{
    bool isclicked = false;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "MyProject");
    inputfield InputFieldA;
    inputfield InputFieldB; 
    inputfield InputFieldC;
    Button buttn;
   
   
   sf::Text text;
   sf::Font font;
   text = sf::Text("Done", font, 30);
   text.setFillColor(sf::Color::Black);
   text.setPosition(810, 500);
   font.loadFromFile("arial.ttf");

   sf::Text textA;
   textA = sf::Text("A", font, 30);
   textA.setFillColor(sf::Color::Black);
   textA.setPosition(700, 200);
   font.loadFromFile("arial.ttf");

   sf::Text textB;
   textB = sf::Text("B", font, 30);
   textB.setFillColor(sf::Color::Black);
   textB.setPosition(700, 300);
   font.loadFromFile("arial.ttf");

   sf::Text textC;
   textC = sf::Text("C", font, 30);
   textC.setFillColor(sf::Color::Black);
   textC.setPosition(700, 400);
   font.loadFromFile("arial.ttf");


    buttn.CreateButton();
    InputFieldA.createInputField(sf::Vector2f(750, 200), sf::Vector2f(200, 40));
    InputFieldB.createInputField(sf::Vector2f(750, 300), sf::Vector2f(200, 40));
    InputFieldC.createInputField(sf::Vector2f(750, 400), sf::Vector2f(200, 40));

    graphic Gr;
    Gr.creategraphic();
    while (window.isOpen())
    {
        sf::Vector2i mousePoz = sf::Mouse::getPosition(window);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputFieldA.handleInput(event);
            InputFieldB.handleInput(event);
            InputFieldC.handleInput(event);


            sf::Vector2i mousePoz = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttn.button.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                    if (!InputFieldA.str.empty() && !InputFieldB.str.empty() && !InputFieldC.str.empty()) {

                        Gr.a = std::stod(InputFieldA.str);
                        Gr.b = std::stod(InputFieldB.str);
                        Gr.c = std::stod(InputFieldC.str);

                        Gr.createparabola();

                    }
                }
            }
            
            

        }


        
        window.clear(sf::Color::White);
        InputFieldA.update();
        InputFieldA.draw(window);
        InputFieldB.update();
        InputFieldB.draw(window);
        InputFieldC.update();
        InputFieldC.draw(window);
        window.draw(Gr.x_axis);
        window.draw(Gr.y_axis);
        window.draw(buttn.button); 
        window.draw(text);
        window.draw(textA);
        window.draw(textB);
        window.draw(textC);
        
        if (Gr.iscreated == true) {
            window.draw(Gr.quadratic);
        }
        window.display();
    }
}
