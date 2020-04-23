#include "draw_smf.hpp"
#include "Player.hpp"

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

void Gra::draw_background(std::list<Frame> &rendrer_list) {
  sf::RectangleShape block;
  block.setFillColor(sf::Color(0x62665f));
  block.setSize(sf::Vector2f(1280, 720));
  rendrer_list.push_back(Frame(block, 1, {-1, 0}));
}

void Gra::draw_table(std::list<Frame> &rendrer_list, Game_state &game,
                     sf::Vector2f lu_point, sf::Vector2f rd_point) {
  std::list<Frame> buffer;
  sf::Vector2f size = rd_point - lu_point;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      sf::RectangleShape block;
      block.setSize(size / 8);
      block.setPosition(size.x / 8 * j, size.y / 8 * i);
      block.move(lu_point);
      if ((i + j) % 2) {
        block.setFillColor(sf::Color::Black);
      } else {
        block.setFillColor(sf::Color::White);
      }
      rendrer_list.push_back(Frame(block, 1, {i, j}));

      char t = game.get_cell({i, j});
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
        buffer.push_back(Frame(block, 0, {i, j}));
      }
    }
  }
  for (auto &t : buffer) {
    rendrer_list.push_back(t);
  }
}

void Gra::draw_possible(std::list<Frame> &render_list, Game_state &game_state,
                        board_cell past, sf::Vector2f lu_point,
                        sf::Vector2f rd_point) {
  sf::Vector2f size = rd_point - lu_point;
  auto b = game_state.get_list_of_correct_moves(game_state.who_moves(), past);
  for (auto &a : b) {
    sf::RectangleShape block;
    block.setSize(size / 8);
    block.setPosition(size.x / 8 * a.y, size.y / 8 * a.x);
    block.move(lu_point);
    block.setFillColor(sf::Color::Blue);
    render_list.push_back(Frame(block, 0, {0}));
  }
}

void Gra::drawing() {
  for (auto &elem : render_list) {
    window.draw(elem.picture);
  }

  window.display();
}

void Gra::update(Game_state &game_state, controller::IPlayer *player) {
  render_list.clear();
  window.clear();
  pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  draw_background(render_list);
  draw_table(render_list, game_state);
  if (game_state.who_moves() == player->turn) {
    draw_possible(render_list, game_state, past);
  }
}

void Gra::compiling_event(Game_state &game_state) {
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (event.type == sf::Event::MouseButtonPressed)
      if (event.mouseButton.button == sf::Mouse::Left) {

        auto res = collision(pos);

        int x = res.data[1];
        int y = res.data[0];

        board_cell next = {y, x};

        if (game_state.check_move(game_state.who_moves(), past, next)) {
          events.push(new controller::MoveEvent(past, next));
        }
        past = next;
      }
  }
}

Gra::Frame &Gra::collision(sf::Vector2f posi) {
  Frame *res;
  for (auto &elem : render_list) {
    auto pic = elem.picture;
    if ((pic.getPosition() < posi) &&
        ((pic.getPosition() + pic.getSize()) > pos) && elem.solid) {
      res = &elem;
    }
  }
  return *res;
}

std::queue<controller::Event *> &Gra::get_events() { return events; }