#include "draw_smf.hpp"

sf::Vector2f operator/(sf::Vector2f vec, int i) {
  vec.x /= i;
  vec.y /= i;
  return vec;
}

bool operator<(sf::Vector2f a, sf::Vector2f b) {
  return (a.x < b.x) && (a.y < b.y);
}
bool operator>(sf::Vector2f a, sf::Vector2f b) {
  return (a.x > b.x) && (a.y > b.y);
}

void draw_background(std::list<sf::RectangleShape> &rendrer_list) {
  sf::RectangleShape block;
  block.setFillColor(sf::Color(0x62665f));
  block.setSize(sf::Vector2f(1280, 720));
  rendrer_list.push_back(block);
}

void draw_table(std::list<sf::RectangleShape> &rendrer_list, Game_state &game,
                sf::Vector2f lu_point, sf::Vector2f rd_point) {
  std::list<sf::RectangleShape> buffer;
  sf::Vector2f size = rd_point - lu_point;
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      sf::RectangleShape block;
      block.setSize(size / 8);
      block.setPosition(size.x / 8 * j, size.y / 8 * i);
      block.move(lu_point);
      if ((i + j) % 2) {
        block.setFillColor(sf::Color::Black);
      } else {
        block.setFillColor(sf::Color::White);
      }
      rendrer_list.push_back(block);

      char t = game.get(j, i);
      if (t != '.') {
        switch (t) {
        case 'b':
          block.setFillColor(sf::Color::Red);
          break;

        case 'w':
          block.setFillColor(sf::Color::Yellow);
          break;

        case 'B':
          block.setFillColor(sf::Color::Red);
          break;

        case 'W':
          block.setFillColor(sf::Color::Yellow);
          break;
        }
        buffer.push_back(block);
      }
    }
  }
  for (auto &t : buffer) {
    rendrer_list.push_back(t);
  }
}

void draw_possible(std::list<sf::RectangleShape> &render_list,
                   Game_state &game_state, std::pair<int, int> past,
                   sf::Vector2f lu_point, sf::Vector2f rd_point) {
  sf::Vector2f size = rd_point - lu_point;
  auto b = game_state.get_list_of_correct_moves(game_state.who_moves(), past);
  for (auto &a : b) {
    std::cerr << b.size() << ' ' << size.x << size.y << ' ' << a.first
              << a.second << std::endl;
    sf::RectangleShape block;
    block.setSize(size / 8);
    block.setPosition(size.x / 8 * a.second, size.y / 8 * a.first);
    block.move(lu_point);
    block.setFillColor(sf::Color::Blue);
    render_list.push_back(block);
  }
}