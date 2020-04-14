#include "draw_smf.hpp"

sf::Vector2f operator /(sf::Vector2f vec, int i) {
    vec.x /= i;
    vec.y /= i;
    return vec;
}

bool operator <(sf::Vector2f a, sf::Vector2f b) {
    return (a.x < b.x) && (a.y < b.y);
}
bool operator >(sf::Vector2f a, sf::Vector2f b) {
    return (a.x > b.x) && (a.y > b.y);
}

void draw_background(std::list<sf::RectangleShape>& rendrer_list) {
    sf::RectangleShape block;
    block.setFillColor(sf::Color::Green);
    block.setSize(sf::Vector2f(1280, 720));
    rendrer_list.push_back(block);
}

void draw_table(std::list<sf::RectangleShape>& rendrer_list, sf::Vector2f lu_point, sf::Vector2f rd_point) {
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
            rendrer_list.push_back(block);
        }
    }
}