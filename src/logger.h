#ifndef LOGGER_H
#define LOGGER_H

#define LOG_MESSAGE(msg)  std::cout << "[LOG]"     << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << std::endl;
#define LOG_TRACE(msg)    std::cout << "[TRACE]"   << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << std::endl;
#define LOG_WARNING(msg)  std::cout << "[WARNING]" << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << std::endl;
#define LOG_ERROR(msg)    std::cerr << "[ERROR]"   << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << std::endl;

#endif