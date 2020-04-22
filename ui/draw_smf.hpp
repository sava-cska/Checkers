#pragma once

#include <SFML/Graphics.hpp>
#include "Event.hpp"
#include "game.hpp"
#include <list>
#include <queue>
#include <iostream>

sf::Vector2f operator/(sf::Vector2f, int);
bool operator<(sf::Vector2f, sf::Vector2f);
bool operator>(sf::Vector2f, sf::Vector2f);

class Gra {
private:
  class Frame {
  public:
    sf::RectangleShape picture;
    bool solid;
    std::vector<int> data;
    Frame(sf::RectangleShape ins, bool inb = 0, std::vector<int> ind = {})
        : picture(ins), solid(inb), data(ind) {}
  };

  std::queue<controller::Event *> events;

  std::list<Frame> render_list;
  sf::Vector2f pos = {0, 0};
  sf::Event event;

  board_cell past = {-1, 0};

public:
  sf::RenderWindow window = {sf::VideoMode(1280, 720), "Chess"};
  void update(Game_state &game_state);
  void drawing();
  void compiling_event(Game_state &game_state);
  Frame &collision(sf::Vector2f);

  std::queue<controller::Event *> &get_events();

private:
  void draw_background(std::list<Frame> &rendrer_list);
  void draw_table(std::list<Frame> &rendrer_list, Game_state &,
                  sf::Vector2f lu_point = sf::Vector2f(320, 40),
                  sf::Vector2f rd_point = sf::Vector2f(960, 680));
  void draw_possible(std::list<Frame> &render_list, Game_state &game_state,
                     board_cell past,
                     sf::Vector2f lu_point = sf::Vector2f(320, 40),
                     sf::Vector2f rd_point = sf::Vector2f(960, 680));
};