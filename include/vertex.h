#ifndef VERTEX_H
#define VERTEX_H

#include <array>
#include <cstdint>

/* vertex attributes */
using position_t  = std::array<float,   2>;
using color8_t    = std::array<uint8_t, 3>;
using textcd_t    = std::array<float,   2>;

struct vertex_t
{
  position_t  position;
  color8_t    color;
  textcd_t    textcd;
};


#endif