#ifndef CHECKERS_SERVER_SERVER_HPP_
#define CHECKERS_SERVER_SERVER_HPP_

#include <SFML/Network.hpp>

#include <stdexcept>
#include <string>
#include <iostream>

class Server {
private:
  const int PORT;

public:
  class Exception : public std::logic_error {
  public:
    Exception(std::string);
  };

public:
  Server(int port = 24310) ;
  void run();
};

#endif // CHECKERS_SERVER_SERVER_HPP_
