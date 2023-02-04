#include "include/core_minimal.h"
#include "include/box.h"
#include "include/shader.h"
#include "include/texture.h"
#include "include/window_manager.h"

extern gn::WindowManager gWindowManager;

namespace gn
{
  
  Box::Box(vec2 dimension_, vec2 position_) 
  : Object(), dimension{dimension_}, position{position_}
  {
    name = "Box_" + std::to_string(id);

    init();
  }

  void Box::init()
  {
    // default vertex positions 
    static const std::array<position_t, 4>  localspace = {
      position_t{ -1, -1 }, // bottom left
      position_t{ +1, -1 }, // bottom right
      position_t{ -1, +1 }, // top left
      position_t{ +1, +1 }  // top right
    };
    // default vertex indices 
    static const std::array<uint8_t, 6>     indices = {
      0,1,3,  // tl - tr -  bl
      0,2,3   // tl - bl - br
    };
    // default color values 
    static const std::array<color8_t, 4>    colors = {
      color8_t{ 255, 255, 255 },  // top left
      color8_t{ 255, 255, 255 },  // top right
      color8_t{ 255, 255, 255 },  // bottom left
      color8_t{ 255, 255, 255 },  // bottom right
    };
    // default texture coordinates 
    static const std::array<textcoord_t, 4> textcoords = {
      textcoord_t{ 0.f, 0.f },  // top left
      textcoord_t{ 1.f, 0.f },  // top right
      textcoord_t{ 0.f, 1.f },  // bottom left
      textcoord_t{ 1.f, 1.f },  // bottom right
    };

    // create vertex array 
    m_vaOBJ = std::unique_ptr<VertexArray>(new VertexArray);
    
    // create vertex buffer 
    m_vbOBJ = std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>(
      new Buffer<GL_ARRAY_BUFFER>(sizeof(localspace) + sizeof(colors) + sizeof(textcoords)));
    
    // create and init index buffer 
    m_ibOBJ = std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>>(
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

  void Box::render(Shader* shader)
  {
    const vec2ui windowSize = gWindowManager.getWindowSize();

    const mat4 scale       = glm::scale(mat4(1.f), vec3(
                                    dimension * 0.5f, 0.f));
    const mat4 translate   = glm::translate(mat4(1.f), vec3(
                                    position.x + dimension.x/2,
                                    position.y + dimension.y/2, 
                                    0.f));
    const mat4 model       = translate * m_rotatemat * scale;
    const mat4 projection  = ortho(0.f, 
                                  (float)windowSize.x, 
                                  (float)windowSize.y, 
                                  0.f, -1.0f, 1.0f);

    shader->use();
    shader->setMatrix4("model", model);
    shader->setMatrix4("projection", projection);

    // bind textures on corresponding texture units
    texture->use();
    texture->bind();
    
    m_vaOBJ.get()->bind();
    glDrawElements(drawmode, 6, GL_UNSIGNED_BYTE, 0);
  }

  void Box::setColor(color8_t color)
  {
    std::array<color8_t, 4> arrcolor = { color,color,color,color };

    m_vbOBJ.get()->namedBufferSubData(
      sizeof(position_t) * 4,
      sizeof(color8_t) * 4,
      arrcolor.data());
  }

  void Box::setTexture(Texture* texture) 
  { 
    this->texture = texture; 
  }
}

