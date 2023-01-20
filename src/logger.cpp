#include "logger.h"

#include <string>
#include <iostream>

namespace logger
{
  void log(const std::string& msg, std::ostream& os)
  {
    os << msg << std::endl;
  }
  void trace(const std::string& msg, std::ostream& os)
  {
    os << "[TRACE]" << msg << std::endl;
  }
  void warning(const std::string& msg, std::ostream& os)
  {
    os << "[WARNING]" << msg << std::endl;
  }
  void error(const std::string& msg, std::ostream& os)
  {
    os << "[ERROR]" << msg << std::endl;
  }
};
