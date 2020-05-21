#ifndef CHECKERS_UI_DRAW_SMF_HPP_
#define CHECKERS_UI_DRAW_SMF_HPP_

#include "Event.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <memory>

sf::Vector2f operator/(sf::Vector2f, int);
bool operator<(sf::Vector2f, sf::Vector2f);
bool operator>(sf::Vector2f, sf::Vector2f);

namespace controller {
class IPlayer;
}

class Gra {
private:
  class Frame {
  public:
    sf::RectangleShape picture;
    bool solid;
    std::string path;
    std::vector<int> data;
    std::string data2 = "";
    Frame(sf::RectangleShape ins, bool inb = 0, std::vector<int> ind = {-1, 0},
          std::string instr = "")
        : picture(ins), solid(inb), data(ind), data2(instr) {}
  };

  

  std::queue<std::shared_ptr<controller::Event>> events;

  std::list<Frame> render_list;
  sf::Vector2f pos = {0, 0};
  sf::Event event;

  BoardCell past = {-1, 0};

  sf::Texture b;
  sf::Texture B;
  sf::Texture w;
  sf::Texture W;

  int number_of_showing_state = 0;

  std::map<char, sf::Texture *> sprites;

  int update_checker = 0;

  float possition_of_scroll = 0; // [0, 0.9]
  bool press_the_scroll = 0;

public:
  sf::RenderWindow window = {sf::VideoMode(1280, 720), "Chess"};
  void update(Game &game, controller::IPlayer *player);
  void drawing();
  void compiling_event(Game &game);
  Frame &collision(sf::Vector2f);

  std::queue<std::shared_ptr<controller::Event>> &get_events();

  Gra();

private:
  void draw_turn(std::list<Frame> &render_list,
                  std::string , int number, 
                  sf::Vector2f lu_point,
                  sf::Vector2f rd_point);
  void draw_background(std::list<Frame> &rendrer_list);
  void draw_table(std::list<Frame> &rendrer_list, GameState &, int collision,
                  sf::Vector2f lu_point = sf::Vector2f(320, 40),
                  sf::Vector2f rd_point = sf::Vector2f(960, 680));
  void draw_history(std::list<Frame> &render_list,  int maximum,
                     sf::Vector2f lu_point = sf::Vector2f(40, 40),
                     sf::Vector2f rd_point = sf::Vector2f(280, 680));
  void draw_possible(std::list<Frame> &render_list, GameState &game_state,
                     BoardCell past,
                     sf::Vector2f lu_point = sf::Vector2f(320, 40),
                     sf::Vector2f rd_point = sf::Vector2f(960, 680));
  void draw_SafeLoad(std::list<Frame> &render_list,
                     sf::Vector2f lu_point = sf::Vector2f(40, 40),
                     sf::Vector2f rd_point = sf::Vector2f(280, 120));
};

#endif
