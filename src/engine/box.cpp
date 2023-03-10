#include "engine/core/core.h"

#include "engine/box.h"
#include "engine/core/shader/shader.h"
#include "engine/texture.h"

#include "engine/subsystems/window_manager.h"

namespace gn
{
  // --- static data -------
  // -----------------------
  const array<position_t, 4>  Box::localspace = {
    position_t{ -1, -1 }, // bottom left
    position_t{ +1, -1 }, // bottom right
    position_t{ -1, +1 }, // top left
    position_t{ +1, +1 }  // top right
  };
  const array<uint8_t, 6>     Box::indices    = {
    0,1,3,  // tl - tr -  bl
    0,2,3   // tl - bl - br
  };
  const array<textcoord_t, 4> Box::textcoords = {
    textcoord_t{ 0.f, 0.f },  // top left
    textcoord_t{ 1.f, 0.f },  // top right
    textcoord_t{ 0.f, 1.f },  // bottom left
    textcoord_t{ 1.f, 1.f },  // bottom right
  };

  Box::Box(
    uint32_t  id,
    string    name,
    vec2      position,
    vec2      size,
    vec2      scaling, 
    float     rotation,  
    Texture*  texture 
  ) 
  : ObjectBase(id, name),
    position{position},
    size{size},
    scaling{scaling},
    rotation{rotation},
    texture{texture}
  {
    initBuffers();
  }

  void Box::initBuffers()
  {
    const array<color8_t, 4> colors = { m_color,m_color,m_color,m_color };

    // create vertex array 
    m_vaOBJ = unique_ptr<VertexArray>(new VertexArray);
    
    // create vertex buffer 
    m_vbOBJ = unique_ptr<Buffer<GL_ARRAY_BUFFER>>(
      new Buffer<GL_ARRAY_BUFFER>(sizeof(localspace) + sizeof(colors) + sizeof(textcoords)));
    
    // create and init index buffer 
    m_ibOBJ = unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>>(
      new Buffer<GL_ELEMENT_ARRAY_BUFFER>(sizeof(indices), indices.data()));

    // init vertex buffer 
    m_vbOBJ.get()->namedBufferSubData(0, sizeof(localspace), localspace.data());
    m_vbOBJ.get()->namedBufferSubData(sizeof(localspace), sizeof(colors), colors.data());
    m_vbOBJ.get()->namedBufferSubData(sizeof(localspace)+sizeof(colors), sizeof(textcoords), textcoords.data());

    // setup vertex attributes
    m_vaOBJ.get()->enableAttribute(0);  // 0.vertex position
    m_vaOBJ.get()->enableAttribute(1);  // 1.vertex color
    m_vaOBJ.get()->enableAttribute(2);  // 2.vertex textcoord

    m_vaOBJ.get()->setAttribFormat(0, 2, GL_FLOAT, false, 0);
    m_vaOBJ.get()->setAttribFormat(1, 3, GL_UNSIGNED_BYTE, true, sizeof(localspace));
    m_vaOBJ.get()->setAttribFormat(2, 2, GL_FLOAT, false, sizeof(localspace) + sizeof(colors));
    
    m_vaOBJ.get()->setAttribBinding(0, 0);
    m_vaOBJ.get()->setAttribBinding(1, 1);
    m_vaOBJ.get()->setAttribBinding(2, 2);

    m_vaOBJ.get()->bindVertexBuffer(0, m_vbOBJ.get(), 0, sizeof(position_t));
    m_vaOBJ.get()->bindVertexBuffer(1, m_vbOBJ.get(), 0, sizeof(color8_t));
    m_vaOBJ.get()->bindVertexBuffer(2, m_vbOBJ.get(), 0, sizeof(textcoord_t));
  }

  void Box::getTransform(transform_t& outTransform)
  {
    outTransform.translate = translate(outTransform.translate, vec3(position, 0.f));
    outTransform.scale = scale(outTransform.scale,  vec3(size.x*scaling.x, size.y*scaling.y, 0.f));
    outTransform.rotate = rotate(outTransform.rotate, rotation, vec3(0.f, 0.f, 1.f));
  }

  void Box::setColor(color8_t color)
  {
    m_color = color;

    array<color8_t, 4> arrcolor = { m_color,m_color,m_color,m_color };
    m_vbOBJ.get()->namedBufferSubData(sizeof(position_t)*4, sizeof(color8_t)*4, arrcolor.data());
  }


}

