//
// Created by pospelov on 18.04.2020.
//
#include "draw_smf.hpp"
#include "game.hpp"
#include <iostream>
#include <string>

int main() {
  Game_state game_state;

  sf::RenderWindow window;
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(1280, 720), "Chess");

  board_cell past_cell = {0, -1};

  while (window.isOpen()) {
    sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    std::list<sf::RectangleShape> rendrer_list;

    sf::Event event;

    window.clear();
    draw_background(rendrer_list);
    draw_table(rendrer_list, game_state);
    draw_possible(rendrer_list, game_state, past_cell);

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

          board_cell current_cell = {count / 8, count % 8};

          game_state.move(game_state.who_moves(), past_cell, current_cell);

          past_cell = current_cell;
        }
    }

    for (auto &elem : rendrer_list) {
      window.draw(elem);
    }

    window.display();
  }

  return 0;
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
