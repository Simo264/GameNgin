#include "engine/core/core.h"

#include "file_manager.h"

#include "engine/core/IO/logger.h"

namespace gn
{
  void FileManager::write(const string& filename, const string& data, bool append)
  {
    ofstream file;
    if(append)
      file.open(filename, ios::out | ios::app);
    else
      file.open(filename, ios::out);
    
    if(!file.is_open())
    {
      LOG_WARNING("FileManager::write - Unable to open file");
      return;
    } 
    file << data;
    file.close();
  }
  
  void FileManager::read(const string& filename, string& destbuffer)
  {
    ifstream file(filename, ios::in);

    if(!file.is_open())
    {
      LOG_WARNING("FileManager::read - Unable to open file");
      return;
    }

    destbuffer.clear();
    
    string line;
    line.reserve(100);

    while(getline(file, line))
      destbuffer.append(line + "\n");

    file.close();
  }

  void FileManager::read(const string& filename, vector<string>& destbuffer)
  {
    ifstream file(filename, ios::in);

    if(!file.is_open())
    {
      LOG_WARNING("FileManager::read - Unable to open file");
      return;
    }

    destbuffer.clear();
    
    string line;
    line.reserve(100);

    while(getline(file, line))
      destbuffer.push_back(line);

    file.close();
  }

  // void FileManager::readbinary(const string& filename, string& destbuffer)
  // {
  //   ifstream file(filename, ios::in | ios::binary);

  //   if(!file.is_open())
  //   {
  //     LOG_WARNING("FileManager::readbinary - Unable to open file");
  //     return;
  //   }

  //   streampos size = file.tellg();
    
  //   destbuffer.clear();
  //   destbuffer.reserve(size);

  //   file.seekg(0, ios::beg);
  //   file.read(&destbuffer[0], size);
  //   file.close();
  // }

}

