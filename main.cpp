#include "draw_smf.hpp"
#include "game.hpp"

#include <iostream>
#include <string>

int main() {
  Gra core;

  Game_state game_state;

  sf::RenderWindow window;

  while (core.window.isOpen()) {
    core.update(game_state);
    core.compiling_event(game_state);
    core.drawing();
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
