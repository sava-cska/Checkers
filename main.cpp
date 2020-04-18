#include "draw_smf.hpp"
#include "model.hpp"
#include <iostream>
#include <string>

int main() {
  Game_state game_state;

  sf::RenderWindow window;
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(1280, 720), "Chess");

  std::pair<int, int> past = {0, -1};

  while (window.isOpen()) {
    sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    std::list<sf::RectangleShape> rendrer_list;


    sf::Event event;

    window.clear();
    draw_background(rendrer_list);
    draw_table(rendrer_list, game_state);
    draw_possible(rendrer_list, game_state, past);

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed)
        if (event.mouseButton.button == sf::Mouse::Left) {

          int count = -1;
          int count1 = -1;
          for (auto &elem : rendrer_list) {
            if ((elem.getPosition() < pos) &&
                (elem.getPosition() + elem.getSize()) > pos) {
              count = count1;
            }
            count1++;
            if (count1 > 63)
              break;
          }

          int x = count % 8;
          int y = count / 8;

          std::cerr << past.first << ' ' << past.second << "     " << y << ' '
                    << x << '\n';

          game_state.move(game_state.who_moves(), past, std::make_pair(y, x));

          past = {y, x};
        }
    }

    for (auto &elem : rendrer_list) {
      window.draw(elem);
    }

    window.display();
  }

  return 0;
}

int main() {

}
/*

int main() {
  Ui ui;
  Model model;
  std::thread([] {
    while (true) {
      ui.draw();
    }
  });
  std::thread([] {
    while (true) {
      update_logic();
    }
  });
  std::thread([] {

  });
}*/
