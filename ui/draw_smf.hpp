#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <list>
#include <string>
#include <iostream>

sf::Vector2f operator /(sf::Vector2f, int);
bool operator <(sf::Vector2f, sf::Vector2f);
bool operator >(sf::Vector2f, sf::Vector2f);

void draw_background(std::list<sf::RectangleShape>& rendrer_list);
void draw_table(std::list<sf::RectangleShape>& rendrer_list, Game_state&,
 sf::Vector2f lu_point = sf::Vector2f(320, 40), sf::Vector2f rd_point = sf::Vector2f(960, 680));
void draw_possible(std::list<sf::RectangleShape>& render_list, Game_state& game_state,board_cell past,
 sf::Vector2f lu_point = sf::Vector2f(320, 40), sf::Vector2f rd_point = sf::Vector2f(960, 680));