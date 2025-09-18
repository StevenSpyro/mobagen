#include "PrimExample.h"
#include "../World.h"
#include "Random.h"
#include <cstdlib>

namespace {
  void RemoveWall(World* w, const Point2D& a, const Point2D& b) {
    if (a.x == b.x) {
      if (a.y < b.y) {
        w->SetSouth(a, false);
        w->SetNorth(b, false);
      }
      else {
        w->SetSouth(a, false);
        w->SetSouth(b, false);
      }
    }
    else if (a.y == b.y) {
      if (a.x < b.x) {
        w->SetEast(a, false);
        w->SetWest(b, false);
      }
      else {
        w->SetWest(a, false);
        w->SetEast(b, false);
      }
    }
  }
}

bool PrimExample::Step(World* w) {
  int sideOver2 = w->GetSize() / 2;

  // todo: code this

  if (!initialized) {
    Point2D start(0, 0);

    toBeVisited.push_back(start);
    w->SetNodeColor(start, Color::Pink); //Color
    initialized = true;
  }

  if (toBeVisited.empty()) {
    return false;
  }

  int idx = std::rand() % toBeVisited.size();
  Point2D current = toBeVisited[idx];

  auto visitables = getVisitables(w, current);

  if (!visitables.empty()) {
    Point2D next = visitables[std::rand() % visitables.size()];
    RemoveWall(w, current, next);
    w->SetNodeColor(next, Color::Green); //Color
    toBeVisited.push_back(next);
  }
  else {
    toBeVisited.erase(toBeVisited.begin() + idx);
  }

  return true;
}

void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;

  // todo: code this

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // todo: code this

  return neighbors;
}
