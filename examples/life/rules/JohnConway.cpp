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

  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      if (dx == 0 && dy == 0) continue;         //Skip;
      size_t ny = (y + dy + lines) % lines;     //Vertical
      size_t nx = (x + dx + columns) % columns; //Horizontal
      if (get(ny, nx)) count++;
    }
  }

  return count;
}
