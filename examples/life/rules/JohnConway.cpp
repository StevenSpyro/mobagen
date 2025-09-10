#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int sideSize = world.SideSize();

  for (int y = 0; y < sideSize; ++y) {
    for (int x = 0; x < sideSize; ++x) {
      Point2D point{x, y};
      int neighbors = CountNeighbors(world, point);
      bool alive = world.Get(point);
      bool nextAlive = false;

      if (alive) {
        nextAlive = (neighbors == 2 || neighbors == 3);
      } else {
        nextAlive = (neighbors == 3);
      }

      world.SetNext(point, nextAlive);
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int count = 0;
  int sideSize = world.SideSize();

  const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

  for (int i = 0; i < 8; ++i) {
    Point2D neighbor{point.x + dx[i], point.y + dy[i]};
    if (world.Get(neighbor)) count++;
  }

  return count;
}
