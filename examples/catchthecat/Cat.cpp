#include "Cat.h"
#include "World.h"
#include "Agent.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  /*
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
  */

  std::vector<Point2D> path = Agent::generatePath(world);

  if (!path.empty()) {
    // Go to exit
    return path.front();
  }

  // Trapped?
  return world->getCat();
}
