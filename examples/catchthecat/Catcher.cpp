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

  auto neighbors = world->getVisitableNeighbors(world->getCat());

  // Making the catcher AI a bit random with how it plays because I don't like the constant circle.

  //Had chance to hopefully balance out, but uh nope.
  //int choice = Random::Range(0, 100);

  // Search for the next step and try to block it
  if (!path.empty()) {
    Point2D exit = path.back();

    if (world->catcherCanMoveToPosition(exit)) {
      return exit;
    }
  }

  // Currently places alongside the cat in the pathway
  if (!path.empty()) {
    // Block the Kitty
    Point2D blockPath = path.front();

    if (world->catcherCanMoveToPosition(blockPath)) {
      return blockPath;
    }
  }

  // Place randomly
  if (!neighbors.empty()) {
    Point2D p = neighbors[Random::Range(0, neighbors.size() - 1)];
    if (world->catcherCanMoveToPosition(p)) {
      return p;
    }
  }

  // Original method
  if (!path.empty() && world->catcherCanMoveToPosition(path.back())) {
    return path.back();
  }

  // Block next
  if (!path.empty() && world->catcherCanMoveToPosition(path.front())) {
    return path.front();
  }

  // Attack Neighbor
  if (!neighbors.empty()) {
    return neighbors.front();
  }

  // Random place
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    if (world->catcherCanMoveToPosition(p)) {
      return p;
    }
  }

}
