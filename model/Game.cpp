#include "Game.hpp"
#include <cassert>

Game::Game() {
  current = GameState();
  game.push_back(current);
}

int Game::number_of_states() const { return (int)game.size(); }

void Game::return_to_state(int number) {
  if (number < 0 || number >= (int)game.size())
    assert(0);
  while ((int)game.size() != number + 1)
    game.pop_back();
  current = game.back();
  return;
}

GameState Game::watch_state(int number) const {
  if (number < 0 || number >= (int)game.size())
    assert(0);
  return game[number];
}

GameState Game::return_current_state() const { return current; }

void Game::move(number_of_player player, BoardCell from, BoardCell to) {
  GameState copy = current;
  current.move(player, from, to);
  if (current != copy)
    game.push_back(current);
  return;
}

void Game::save_to_file(const std::string &file) const {
  std::ofstream os(file);
  os << "<Game>\n";
  for (int i = 0; i < (int)game.size(); i++)
    game[i].save_to_file(os);
  os << "</Game>\n";
}

struct helper {
  Game g;
  GameState state;
  std::string tag;
  int row;
};

void XMLCALL startElement(void *userData, const XML_Char *name,
                          const XML_Char **atts) {
  helper *ptr = (helper *)userData;
  ptr->tag = name;
  if ((std::string)name == "GameState")
    ptr->row = 0;
  return;
}

void XMLCALL endElement(void *userData, const XML_Char *name) {
  helper *ptr = (helper *)userData;
  if (ptr->tag == "GameState")
    (ptr->g).game.push_back(ptr->state);
  return;
}

void XMLCALL dataElement(void *userData, const XML_Char *s, int len) {
  helper *ptr = (helper *)userData;
  if (ptr->tag == "board") {
    assert(ptr->row < (ptr->state).SIZE);
    int col = 0;
    for (int i = 0; i < len && col < (ptr->state).SIZE; i++)
      if (s[i] == '.' || s[i] == 'w' || s[i] == 'W' || s[i] == 'b' ||
          s[i] == 'B')
        (ptr->state).board[ptr->row][col++] = s[i];
  }
  if (ptr->tag == "who_move_last") {
    for (int i = 0; i < len; i++) {
      if (s[i] == '1')
        ptr->state.who_last = FIRST;
      if (s[i] == '2')
        ptr->state.who_last = SECOND;
    }
  }
  if (ptr->tag == "he_kill") {
    for (int i = 0; i < len; i++)
      if (s[i] == '1' || s[i] == '0')
        ptr->state.type_last = s[i] - '0';
  }
  if (ptr->tag == "finish_cell_last_move") {
    int cnt = 0;
    for (int i = 0; i < len;) {
      if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
        std::string str = "";
        str += s[i];
        while (i + 1 < len && s[i + 1] >= '0' && s[i + 1] <= '9') {
          i++;
          str += s[i];
        }
        if (cnt == 0)
          (ptr->state).last_move.x = atoi(str.c_str());
        else
          (ptr->state).last_move.y = atoi(str.c_str());
        cnt++;
      }
      i++;
    }
  }
  if (ptr->tag == "move_to_draw") {
    std::string str = "";
    for (int i = 0; i < len; i++)
      if (s[i] >= '0' && s[i] <= '9')
        str += s[i];
    ptr->state.move_to_draw = atoi(str.c_str());
  }
  return;
}

void Game::load_from_file(const std::string &file) {
  std::ifstream is(file);
  char buf[BUFSIZ];
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;

  helper help;
  XML_SetUserData(parser, &help);
  XML_SetCharacterDataHandler(parser, dataElement);
  XML_SetElementHandler(parser, startElement, endElement);
  do {
    is.read(buf, BUFSIZ);
    int len = is.gcount();
    done = (len < BUFSIZ);
    if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
      std::cerr << XML_ErrorString(XML_GetErrorCode(parser)) << " at line "
                << XML_GetCurrentLineNumber(parser) << '\n';
      XML_ParserFree(parser);
      assert(0);
    }
  } while (!done);
  XML_ParserFree(parser);
  return;
}
