//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
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
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {

  int count = 0;
  int sideSize = world.SideSize();

  //const int dx[6] = {-1, 0, 1, -1, 1, -1};
  //const int dy[6] = {-1, -1, -1, 0, 0, 1};

  int dx[6], dy[6];         //Even
  if (point.y % 2 == 0) {
    dx[0] = -1; dy[0] = -1;
    dx[1] = 0; dy[1] = -1;
    dx[2] = -1; dy[2] = 0;
    dx[3] = 1; dy[3] = 0;
    dx[4] = -1; dy[4] = 1;
    dx[5] = 0; dy[5] = 1;
    } else {                 // ODD
    dx[0] = 0;  dy[0] = -1;
    dx[1] = 1;  dy[1] = -1;
    dx[2] = -1; dy[2] = 0;
    dx[3] = 1;  dy[3] = 0;
    dx[4] = 0;  dy[4] = 1;
    dx[5] = 1;  dy[5] = 1;
  }

  for (int i = 0; i < 6; ++i) {
    Point2D neighbor{point.x + dx[i], point.y + dy[i]};
    if (world.Get(neighbor)) count++;
  }

  return count;
}
