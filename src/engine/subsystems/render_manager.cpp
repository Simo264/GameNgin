#include "engine/core/core.h"

#include "render_manager.h"
#include "window_manager.h"

#include "engine/core/shader/shader.h"
#include "engine/box.h"

namespace gn
{
  void RenderManager::draw(Shader* shader, Box* box)
  {
    transform_t transform; 
    box->getTransform(transform);

    shader->use();
    shader->setMatrix4("model", transform.translate * transform.scale * transform.rotate);
    shader->setMatrix4("projection", WindowManager::getInstance().getOrthographic());

    // use texture
    if(box->texture)
    {
      box->texture->use();
      box->texture->bind();
    }
    
    box->getVertexArray()->bind();
    glDrawElements(drawmode, 6, GL_UNSIGNED_BYTE, 0);
  }

}