#pragma once

#include <SFML/Graphics.hpp>
#include "model.hpp"
#include <list>
#include <string>
#include <iostream>

sf::Vector2f operator /(sf::Vector2f, int);
bool operator <(sf::Vector2f, sf::Vector2f);
bool operator >(sf::Vector2f, sf::Vector2f);

void draw_background(std::list<sf::RectangleShape>& rendrer_list);
void draw_table(std::list<sf::RectangleShape>& rendrer_list, Game_state&,
 sf::Vector2f lu_point = sf::Vector2f(320, 40), sf::Vector2f rd_point = sf::Vector2f(960, 680));
void draw_possible(std::list<sf::RectangleShape>& render_list, Game_state& game_state,std::pair<int,int> past,
 sf::Vector2f lu_point = sf::Vector2f(320, 40), sf::Vector2f rd_point = sf::Vector2f(960, 680));