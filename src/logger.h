#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

namespace logger
{
  void log(const char* filename, int lineno, const std::string& msg = "", std::ostream& os = std::cout);
  void trace(const char* filename, int lineno, const std::string& msg = "", std::ostream& os = std::cout);
  void warning(const char* filename, int lineno, const std::string& msg = "", std::ostream& os = std::cout);
  void error(const char* filename, int lineno, const std::string& msg = "", std::ostream& os = std::cout);
};

#endif