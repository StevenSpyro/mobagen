#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  // find center of mass

  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  Vector2f center= Vector2f::zero();
  int count = 0;

  for (Boid* neighbor : neighborhood) {
    if (neighbor == boid) continue;
    center += neighbor->getPosition();
    count++;
  }

  if (count == 0) return Vector2f::zero();

  center /= (double)count;
  Vector2f desired = center - boid->getPosition();

  return Vector2f::normalized(desired);

  //return cohesionForce;
}