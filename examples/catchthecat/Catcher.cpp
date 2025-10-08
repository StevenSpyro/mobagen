#include "Catcher.h"
#include "World.h"
#include "Agent.h"

Point2D Catcher::Move(World* world) {
  /*
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
  */

  std::vector<Point2D> path = Agent::generatePath(world);

  // Currently places alongside the cat in the pathway
  if (!path.empty()) {
    // Block the Kitty
    Point2D blockPath = path.front();

    if (world->catcherCanMoveToPosition(blockPath)) {
      return blockPath;
    }
  }

  // Other Way to make it harder for the cat
  auto neighbors = world->getVisitableNeighbors(world->getCat());
  if (!neighbors.empty()) {
    return neighbors.front();
  }

}
