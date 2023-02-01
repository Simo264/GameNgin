#include "include/core_minimal.h"
#include "include/collision_detection.h"

bool collision_detection::basic_hitbox(Box* box1, Box* box2)
{
  // b2.x1 <= b1.x1 <= b2.x2 or
  // b2.x1 <= b1.x2 <= b2.x2
  const auto& b1_x1   = box1->position.x - (box1->dimension.x / 2);
  const auto& b1_x2   = box1->position.x + (box1->dimension.x / 2);
  const auto& b2_x1   = box2->position.x - (box2->dimension.x / 2);
  const auto& b2_x2   = box2->position.x + (box2->dimension.x / 2);
  bool collisionX = (b2_x1 < b1_x1  && b1_x1 < b2_x2) or
                    (b2_x1 <= b1_x2 && b1_x2 <= b2_x2);

  // b2.y1 < b1.y2 < b2.y2 or
  // b2.y1 < b1.y1 < b2.y2
  const auto& b1_y1   = box1->position.y - (box1->dimension.y / 2);
  const auto& b1_y2   = box1->position.y + (box1->dimension.y / 2);
  const auto& b2_y1   = box2->position.y - (box2->dimension.y / 2);
  const auto& b2_y2   = box2->position.y + (box2->dimension.y / 2);
  bool collisionY = (b2_y1 <= b1_y2 && b1_y2 <= b2_y2) or
                    (b2_y1 <= b1_y1 && b1_y1 <= b2_y2);

  return (collisionX && collisionY);
}
