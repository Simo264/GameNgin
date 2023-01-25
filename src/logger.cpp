#include "logger.h"

#include <string>
#include <iostream>

namespace logger
{
  void log(const char* filename, int lineno, const std::string& msg, std::ostream& os)
  {
    os << "[LOG]" << "[" << filename << ":" << lineno << "]" << msg << std::endl;
  }
  void trace(const char* filename, int lineno, const std::string& msg, std::ostream& os)
  {
    os << "[TRACE]" << "[" << filename << ":" << lineno << "]" << msg << std::endl;
  }
  void warning(const char* filename, int lineno, const std::string& msg, std::ostream& os)
  {
    os << "[WARNING]" << "[" << filename << ":" << lineno << "]" << msg << std::endl;
  }
  void error(const char* filename, int lineno, const std::string& msg, std::ostream& os)
  {
    os << "[ERROR]" << "[" << filename << ":" << lineno << "]" << msg << std::endl;
  }
};
