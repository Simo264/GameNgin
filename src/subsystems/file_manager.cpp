#include "../core_minimal.h"

#include "file_manager.h"

#include "../logger.h"

namespace gn
{

  void FileManager::write(const std::string& filename, const char* data, bool binary)
  {
    std::ofstream file;

    if(binary)
      file.open(filename, std::ios::out | std::ios::binary);
    else
      file.open(filename, std::ios::out);

    if(!file.is_open())
    {
      LOG_WARNING("FileManager::write - Unable to open file");
      return;
    } 

    file.write(data, strlen(data));
    file.close();
  }

  void FileManager::read(const std::string& filename, std::string& destbuffer)
  {
    std::ifstream file(filename, std::ios::in);

    if(!file.is_open())
    {
      LOG_WARNING("FileManager::read - Unable to open file");
      return;
    }

    destbuffer.clear();
    
    std::string line;
    while(std::getline(file, line))
      destbuffer.append(line + "\n");

    file.close();
  }

  void FileManager::readbinary(const std::string& filename, std::string& destbuffer)
  {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if(!file.is_open())
    {
      LOG_WARNING("FileManager::readbinary - Unable to open file");
      return;
    }

    std::streampos size = file.tellg();
    
    destbuffer.clear();
    destbuffer.reserve(size);

    file.seekg(0, std::ios::beg);
    file.read(&destbuffer[0], size);
    file.close();
  }

}

