#include "../include/globals.h"

namespace globals
{
  uint16_t window_width   = 0;
  uint16_t window_height  = 0;
  
  double world_time       = 0;

  std::map<uint32_t, Object*> world_objects = std::map<uint32_t, Object*>();
};