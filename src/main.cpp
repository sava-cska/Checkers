#include <SFML/Graphics.hpp>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <iostream>

sf::Vector2f operator /(sf::Vector2f vec, int i) {
    vec.x /= i;
    vec.y /= i;
    return vec;
}

void draw_background(sf::RenderTarget& target) {
    sf::RectangleShape block;
    block.setFillColor(sf::Color::Green);
    block.setSize(sf::Vector2f(1280, 720));
    target.draw(block);
}

void draw_table(sf::RenderTarget& target, sf::Vector2f lu_point = sf::Vector2f(320, 40), sf::Vector2f rd_point = sf::Vector2f(960, 680)) {
    sf::Vector2f size = rd_point - lu_point;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            sf::RectangleShape block;
            block.setSize(size / 8);
            block.setPosition(size.x / 8 * j, size.y / 8 * i);
            block.move(lu_point);
            if((i + j) % 2) {
                block.setFillColor(sf::Color::Black);
            } else {
                block.setFillColor(sf::Color::White);
            }
            target.draw(block);
        }
    }
}

int main() {
    sf::RenderWindow window;
    window.setFramerateLimit(1);
    window.create(sf::VideoMode(1280, 720), "Chess");

    while (window.isOpen()) {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        sf::Event event;

        window.clear();
        draw_background(window);
        draw_table(window);
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
                if(event.key.code == sf::Mouse::Left) {
                    pos -= sf::Vector2f(320, 40);
                    pos = pos / (620 / 8);
                    std::string a = std::to_string((int)pos.x) + " " + std::to_string((int)pos.y);
                    std::cout << a << std::endl;
                    //move ...
                }
        }
        window.display();
    }

    return 0;
}