#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>
#include <map>

#include "../include/object.h"

namespace globals
{
  extern uint16_t window_width;
  extern uint16_t window_height;

  extern double   world_time;

  extern std::map<uint32_t, Object*> world_objects;
};

#endif