#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

namespace gn
{
  // Static FileManager class 
  // ---------------------------------
  class FileManager
  {
  private:
    FileManager() = default;
    ~FileManager() = default;

  public:
    static void write(const string& filename, const string& data, bool append = false);
    
    static void read(const string& filename, string& destbuffer);
    static void read(const string& filename, vector<string>& destbuffer);
  };
  // ---------------------------------
}
#endif