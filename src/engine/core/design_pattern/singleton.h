#ifndef SINGLETON_H
#define SINGLETON_H

namespace gn
{
  // Singleton template class 
  // --------------------------------------
  template<class T>
  class Singleton
  {
    
  public:
    Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton& other) = delete;
    void operator=(const Singleton&)  = delete;

    static T& getInstance()
    {
      static T instance;
      return instance;
    }
  };
  // --------------------------------------
}

#endif