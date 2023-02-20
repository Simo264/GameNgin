#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

namespace gn
{
  class FileManager
  {
  private:

  public:
    FileManager() = default;
    ~FileManager() = default;

    static void write(const std::string& filename, const char* data, bool binary = false);

    static void append(const std::string& filename, const char* data, bool binary = false);
  
    static void read(const std::string& filename, std::string& destbuffer);
    static void readbinary(const std::string& filename, std::string& destbuffer);
  };
}
#endif