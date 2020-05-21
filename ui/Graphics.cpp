#include "Graphics.hpp"
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

void Gra::draw_table(std::list<Frame> &rendrer_list, GameState &game, int collision,
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
      rendrer_list.push_back(Frame(block, collision, {i, j}));

      char t = game.get_cell({i, j});
      if (t != '.') {
        //?????????????????????????????????????
        block.setFillColor(sf::Color::White);
        //??????????????????????????????????????
        block.setTexture(sprites[t]);
        buffer.push_back(Frame(block, 0, {i, j}));
      }
    }
  }
  for (auto &t : buffer) {
    rendrer_list.push_back(t);
  }
}

void Gra::draw_possible(std::list<Frame> &render_list, GameState &game_state,
                        BoardCell past, sf::Vector2f lu_point,
                        sf::Vector2f rd_point) {
  sf::Vector2f size = rd_point - lu_point;
  auto b = game_state.get_list_of_correct_moves(game_state.who_moves(), past);
  for (auto &a : b) {
    sf::RectangleShape block;
    block.setSize(size / 8);
    block.setPosition(size.x / 8 * a.y, size.y / 8 * a.x);
    block.move(lu_point);
    block.setFillColor(sf::Color::Blue);
    render_list.push_back(Frame(block, 0, {-1, 0}));
  }
}

void Gra::draw_SafeLoad(std::list<Frame> &render_list, sf::Vector2f lu_point,
                        sf::Vector2f rd_point) {
  sf::Vector2f size = rd_point - lu_point;
  size.x = size.x / 2;
  sf::RectangleShape block;
  block.setSize(size);
  block.setPosition({0, 0});
  block.move(lu_point);
  block.setFillColor(sf::Color::Green);
  render_list.push_back(Frame(block, 1, {-2, 0}, "./saves/1.xml"));
  block.move({size.x, 0});
  block.setFillColor(sf::Color::Red);
  render_list.push_back(Frame(block, 1, {-2, 1}, "./saves/1.xml"));
}

void Gra::drawing() {
  for (auto &elem : render_list) {
    window.draw(elem.picture);
  }

  window.display();
}

void Gra::update(Game &game, controller::IPlayer *player) {
  auto state = game.watch_state(number_of_showing_state);
  render_list.clear();
  window.clear();
  pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  draw_background(render_list);
  draw_table(render_list, state, (number_of_showing_state == game.number_of_states() - 1) ? 1 : 0);
  if (state.who_moves() == player->turn) {
    draw_possible(render_list, state, past);
  }
  draw_history(render_list, game.number_of_states());
}

void Gra::compiling_event(Game &game) {
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (event.type == sf::Event::MouseButtonPressed)
      if (event.mouseButton.button == sf::Mouse::Left) {

        auto res = collision(pos);

        int x = res.data[1];
        int y = res.data[0];

        BoardCell next = {y, x};

        if (game.return_current_state().check_move(game.return_current_state().who_moves(), past, next)) {
          events.push(new controller::MoveEvent(past, next));
          number_of_showing_state = game.number_of_states();
          possition_of_scroll = 0.9;
        }
        past = next;

        if (past.x == -2) {
          if (past.y == 0) {
            game.load_from_file(res.data2);
          } else {
            game.save_to_file(res.data2);
          }
        }

        if (past.x == -3) {
          number_of_showing_state = res.data[1]; 
        }

        if (past.x == -4) {
          game.return_to_state(res.data[1]);  
          number_of_showing_state = res.data[1];     
        }

        if (past.x == -5) {
          press_the_scroll = 1;
        }
      }
    if (event.type == sf::Event::MouseButtonReleased) {
      press_the_scroll = 0;
    }

    if (press_the_scroll) {
          auto posit = pos.y - 32;
          
          posit -= 40;
          if (posit < 0) {
            posit = 0;
          } 
          
          posit = posit / 640;
          
          if (posit > 0.9) {
            posit = 0.9;
          }
          possition_of_scroll = posit;
    }
  }
}

Gra::Frame &Gra::collision(sf::Vector2f posi) {
  Frame *res = 0;
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

void Gra::draw_turn(std::list<Frame> &render_list,
                  std::string , int number, 
                  sf::Vector2f lu_point,
                  sf::Vector2f rd_point) {
  sf::Vector2f size = rd_point - lu_point;
  sf::RectangleShape block;
  block.setSize(size);
  block.setPosition({0, 0});
  block.move(lu_point);
  block.setFillColor(sf::Color::Green);
  block.setOutlineColor(sf::Color::Black);
  block.setOutlineThickness(2);
  sf::Text text;
  /*text.setString(str);
  block.setSize(size / 2);
  block.setPosition({0, 0});
  block.move(lu_point + size / 4);
  //text.getTransform());*/
  render_list.push_back(Frame(block, 1, {-3, number}, ""));
  
  
  lu_point.x += size.x * 7 / 8;
  size = rd_point - lu_point;
  block.setSize(size);
  block.setPosition({0, 0});
  block.move(lu_point);
  block.setFillColor(sf::Color::Cyan);
  render_list.push_back(Frame(block, 1, {-4, number}, ""));
}

void Gra::draw_history(std::list<Frame> &render_list, int maximum,
                     sf::Vector2f lu_point ,
                     sf::Vector2f rd_point ) {
  float dx = rd_point.x - lu_point.y; 
  dx /= 10;
  sf::Vector2f rd_point_old = rd_point;
  rd_point.x -= dx;
  sf::Vector2f delta = {0, (rd_point.y - lu_point.y)};

  sf::Vector2f lu_point_new = rd_point - delta;
  delta = delta / 8;

  rd_point.y = lu_point.y + delta.y;
  for (int i = (int)(maximum * possition_of_scroll); i < std::min(maximum, (int)(maximum * possition_of_scroll) + 8); i++) {
     draw_turn(render_list, "", i, lu_point, rd_point);
     rd_point += delta;
     lu_point += delta;
  }


  //scrollbar
  sf::Vector2f size = rd_point_old - lu_point_new;
  size.x += 2;
  sf::RectangleShape block;
  block.setSize(size);
  block.setPosition({0, 0});
  block.move(lu_point_new);
  block.setFillColor(sf::Color::Black);
  block.setOutlineColor(sf::Color::Black);
  block.setOutlineThickness(2);
  render_list.push_back(Frame(block, 0, {-1, 0}, "")); 

  block.move({0, size.y * possition_of_scroll});
  block.setFillColor(sf::Color::Blue);
  block.setSize({size.x, size.y / 10});
  render_list.push_back(Frame(block, 1, {-5, 0}, ""));
}

Gra::Gra() {
    window.setFramerateLimit(60);
    b.loadFromFile("./sprites/b.png");
    B.loadFromFile("./sprites/B.png");
    W.loadFromFile("./sprites/W.png");
    w.loadFromFile("./sprites/w.png");
    sprites.emplace('b', &b);
    sprites.emplace('B', &B);
    sprites.emplace('W', &W);
    sprites.emplace('w', &w);
  }
