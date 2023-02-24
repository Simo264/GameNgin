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

    static void write(const string& filename, const string& data, bool append = false);
    
    static void read(const string& filename, string& destbuffer);
    static void read(const string& filename, vector<string>& destbuffer);
  };
}
#endif