#ifndef TRANSFORM_H
#define TRANSFORM_H

struct transform_t
{
  mat4 scale      = mat4(1.f);
  mat4 translate  = mat4(1.f);
  mat4 rotate     = mat4(1.f);
};


#endif