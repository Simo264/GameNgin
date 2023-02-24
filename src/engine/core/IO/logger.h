#ifndef LOGGER_H
#define LOGGER_H

#define LOG_MESSAGE(msg)  cout << "[LOG]"     << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << endl;
#define LOG_TRACE(msg)    cout << "[TRACE]"   << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << endl;
#define LOG_WARNING(msg)  cout << "[WARNING]" << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << endl;
#define LOG_ERROR(msg)    cerr << "[ERROR]"   << "[" << __FILE__ << ":" << __LINE__ << "]" << msg << endl;

#endif