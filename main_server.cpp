//
// Created by pospelov on 24.05.2020.
//

#include "CompPlayer.hpp"
#include "Event.hpp"
#include "Game.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "Server.hpp"

#include "tclap/CmdLine.h"

#include <cassert>
#include <iostream>
#include <string>

static void parse_command_line(int argc, char **argv, int &port) {
  try {
    TCLAP::CmdLine cmd("Server for checkers game", ' ', "0.1");
    TCLAP::ValueArg<int> portArg("p", "port", "port", false,
                                       24310, "port for server", cmd);
    cmd.parse(argc, argv);

    port = portArg.getValue();
  } catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " arg " << e.argId() << std::endl;
  }
} // TODO: make special class for it!

int main(int argc, char **argv) {
  int port;
  parse_command_line(argc, argv, port);
  Server server(port);
  try {
    server.run();
    std::cerr << "finished!\n";
  } catch (const Server::Exception &e) {
    std::cerr << e.what();
  }
  return 0;
}