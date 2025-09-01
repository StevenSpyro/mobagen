#include "AlignmentRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/gtc/constants.hpp"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // todo: add your code here to align each boid in a neighborhood
  // Try to match the heading of neighbors = Average velocity
  // hint: iterate over the neighborhood

  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  Vector2f averageVelocity = Vector2f::zero();
  int count = 0;

  for (Boid* neighbor : neighborhood) {
    if (neighbor == boid) continue;
    averageVelocity += neighbor->velocity;
    count++;
  }

  if (count == 0) return Vector2f::zero();

  averageVelocity /= (double)count;

  return Vector2f::normalized(averageVelocity);
}