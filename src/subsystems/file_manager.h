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

    static void write(const std::string& filename, const std::string& data, bool append = false);
    
    static void read(const std::string& filename, std::string& destbuffer);
    static void read(const std::string& filename, std::vector<std::string>& destbuffer);
  };
}
#endif