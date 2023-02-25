#ifndef SINGLETON_H
#define SINGLETON_H

namespace gn
{
  // Singleton template class 
  // --------------------------------------
  template<class T>
  class Singleton
  {
  protected:
    Singleton() = default;
    ~Singleton() = default;

  public:
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