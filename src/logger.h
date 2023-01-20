#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

namespace logger
{
  void log(const std::string& msg, std::ostream& os = std::cout);
  void trace(const std::string& msg, std::ostream& os = std::cout);
  void warning(const std::string& msg, std::ostream& os = std::cout);
  void error(const std::string& msg, std::ostream& os = std::cout);
};

#endif