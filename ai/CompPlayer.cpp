#include "CompPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <thread>

static const int INF = (int)1e9;

int cnt1 = 0, cnt2 = 0;

CompPlayer::CompPlayer(number_of_player turn, int seconds, int deep)
    : controller::IPlayer(turn), seconds_(seconds), deep_(deep) {}

CompPlayer::~CompPlayer() {}

void CompPlayer::set_game_state(const GameState &gs_) { gs = gs_; }

bool CompPlayer::check_move() {
  if (IPlayer::check_move()) {
    return true;
  }
  if (gs.who_moves() == turn && gs.check_win() == state::GAME) {
    auto move = get_next_move(gs, seconds_, deep_);
    gs.move(turn, move.from, move.to);
    add_move(move.from, move.to);
    return true;
  }
  return false;
}

bool CompPlayer::send_move(const BoardCell &from, const BoardCell &to) {
  if (gs.who_moves() != turn) {
    gs.move(gs.who_moves(), from, to);
    return true;
  }
  return false;
}

int CompPlayer::score(const GameState &G) {
  int white_position[8][8] = 
  {
  {64, 63, 62, 61, 60, 59, 58, 57},
  {56, 55, 54, 53, 52, 51, 50, 49},
  {48, 47, 46, 45, 44, 43, 42, 41},
  {40, 39, 38, 37, 36, 35, 34, 33},
  {32, 31, 30, 29, 28, 27, 26, 25},
  {24, 23, 22, 21, 20, 19, 18, 17},
  {16, 15, 14, 13, 12, 11, 10, 9},
  {8, 7, 6, 5, 4, 3, 2, 1}
  };

  int black_position[8][8] = 
  {
  {1, 2, 3, 4, 5, 6, 7, 8},
  {9, 10, 11, 12, 13, 14, 15, 16},
  {17, 18, 19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30, 31, 32},
  {33, 34, 35, 36, 37, 38, 39, 40},
  {41, 42, 43, 44, 45, 46, 47, 48},
  {49, 50, 51, 52, 53, 54, 55, 56},
  {57, 58, 59, 60, 61, 62, 63, 64}
  };

  int only_queen[8][8] = 
  {
  {1, 2, 3, 4, 4, 3, 2, 1},
  {9, 10, 11, 12, 12, 11, 10, 9},
  {17, 18, 19, 20, 20, 19, 18, 17},
  {25, 26, 27, 28, 28, 27, 26, 25},
  {25, 26, 27, 28, 28, 27, 26, 25},
  {17, 18, 19, 20, 20, 19, 18, 17},
  {9, 10, 11, 12, 12, 11, 10, 9},
  {1, 2, 3, 4, 4, 3, 2, 1}
  };
  int ordw = 0, ordb = 0, queenw = 0, queenb = 0;
  int sum_with_w = 0, sum_with_b = 0, sum_out_w = 0, sum_out_b = 0;
  for (int i = 0; i < G.SIZE; i++)
    for (int j = 0; j < G.SIZE; j++) {
      if (G.board[i][j] == 'w')
        ordw++;
      if (G.board[i][j] == 'b')
        ordb++;
      if (G.board[i][j] == 'W')
        queenw++;
      if (G.board[i][j] == 'B')
        queenb++;
      if (G.board[i][j] == 'w' || G.board[i][j] == 'W')
        sum_with_w += white_position[i][j], sum_out_w += only_queen[i][j];
      if (G.board[i][j] == 'b' || G.board[i][j] == 'B')
        sum_with_b += black_position[i][j], sum_out_b += only_queen[i][j];
    }
  if (ordw + ordb > 0)
    return 100 * (ordw - ordb) + 1000 * (queenw - queenb) + sum_with_w - sum_with_b;
  else
    return 1000 * (queenw - queenb) + sum_out_w - sum_out_b;
}

void CompPlayer::alpha_beta(const GameState &G, int alpha, int beta,
                 int deep, std::pair <int, Move> &total, bool flow) {
  cnt1++;
  if (G.move_to_draw >= G.DRAW_MOVE) {
    total = std::make_pair(0, Move());
    return;
  }

  if (deep == 0) {
    total = std::make_pair(score(G), Move());
    return;
  }
  
  bool exist_white = false, exist_black = false;
  for (int i = 0; i < G.SIZE; i++)
    for (int j = 0; j < G.SIZE; j++) {
      if (G.board[i][j] == 'w' || G.board[i][j] == 'W')
        exist_white = true;
      if (G.board[i][j] == 'b' || G.board[i][j] == 'B')
        exist_black = true;
    }
  if (!exist_white || !exist_black) {
    if (exist_white)
      total = std::make_pair(INF, Move());
    else
      total = std::make_pair(-INF, Move());
    return;
  }
  
  //clock_t current_time = clock();
  //if (1.0 * (current_time - start_time) / CLOCKS_PER_SEC > seconds)
    //return std::make_pair(score(G), Move());
  
  number_of_player player = G.who_moves();

  std::vector <Move> moves;
  int delta, up, down, lef, rig;
  if (player == SECOND)
    up = 0, down = G.SIZE, lef = 0, rig = G.SIZE, delta = 1;
  else
    up = G.SIZE - 1, down = -1, lef = G.SIZE - 1, rig = -1, delta = -1;

  for (int i = up; i != down; i += delta)
    for (int j = lef; j != rig; j += delta) {
      std::vector<BoardCell> correct;
      G.get_list_of_correct_moves(player, BoardCell(i, j), correct);
      for (int z = 0; z < (int)correct.size(); z++)
        moves.push_back(Move(BoardCell(i, j), correct[z]));
    }

  if (moves.empty()) {
    if (player == FIRST)
      total = std::make_pair(-INF, Move());
    else
      total = std::make_pair(INF, Move());
    return;
  }

  Move best_move;
  int current_score = (player == FIRST ? -INF : INF);
  bool fl = !G.find_kill(player);
  std::vector <std::pair <int, Move> > res((int)moves.size());

  if (flow) {
    std::vector <std::thread> act;
    for (int i = 0; i < (int)moves.size(); i++) {
      GameState cop = G;
      cop.move(player, moves[i].from, moves[i].to);
      act.push_back(std::thread(alpha_beta, std::ref(cop), alpha, beta, 
                                deep - fl, std::ref(res[i]), false));
      if ((i + 1) % NUMBER_OF_THREADS == 0) {
        for (int j = 0; j < (int)act.size(); j++)
          act[j].join();
        act.clear();
      }
    }
    for (int j = 0; j < (int)act.size(); j++)
      act[j].join();
    act.clear();
  }

  for (int i = 0; i < (int)moves.size(); i++) {
      if (!flow) {
        GameState cop = G;
        cop.move(player, moves[i].from, moves[i].to);
        alpha_beta(cop, alpha, beta, deep - fl, res[i], false);
      }

      if (player == FIRST) {
        if (res[i].first >= current_score) {
          best_move = moves[i];
          current_score = res[i].first;
        }
        alpha = std::max(alpha, res[i].first);
        if (alpha > beta) {
          total = std::make_pair(alpha, moves[i]);
          cnt2++;
          return;
        }
      } else {
        if (res[i].first <= current_score) {
          best_move = moves[i];
          current_score = res[i].first;
        }
        beta = std::min(beta, res[i].first);
        if (alpha > beta) {
          total = std::make_pair(beta, moves[i]);
          cnt2++;
          return;
        }
      }
    }
    total = std::make_pair(current_score, best_move);
    return;
}

Move CompPlayer::get_next_move(const GameState &G, int seconds, int deep) const {
  std::pair<int, Move> result;
  (void)seconds;
  cnt1 = 0, cnt2 = 0;
  clock_t start = clock();
  alpha_beta(G, -INF, INF, deep, result, true);
  clock_t finish = clock();
  std::cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << '\n' <<
            cnt1 << ' ' << cnt2 << '\n';
  return result.second;
}
