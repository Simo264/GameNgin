#ifndef ACTOR_H
#define ACTOR_H

#include "engine/box.h"


namespace gn
{
  class Actor : public Box
  {
  public:
    Actor() = default;
    ~Actor() = default;
  };

}
#endif