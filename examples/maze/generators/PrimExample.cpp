#include "PrimExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>

namespace {
  void RemoveWall(World* w, const Point2D& a, const Point2D& b) {
    if (a.x == b.x) {
      if (a.y < b.y) {
        w->SetSouth(a, false);
        w->SetNorth(b, false);
      } else {
        w->SetNorth(a, false);
        w->SetSouth(b, false);
      }
    } else if (a.y == b.y) {
      if (a.x < b.x) {
        w->SetEast(a, false);
        w->SetWest(b, false);
      } else {
        w->SetWest(a, false);
        w->SetEast(b, false);
      }
    }
  }
}

bool PrimExample::Step(World* w) {
  // todo: code this

  if (!initialized) {
    initialized = true;
    auto sideOver2 = w->GetSize() / 2;
    Point2D start = {-sideOver2, -sideOver2};
    visitedSet.insert(start);
    w->SetNodeColor(start, Color::Red);

    auto vs = getVisitables(w, start);
    toBeVisited.insert(toBeVisited.end(), vs.begin(), vs.end());
  }

  if (toBeVisited.empty()) return false;

  int idx = Random::Range(0, (int)toBeVisited.size() - 1);
  Point2D current = toBeVisited[idx];
  toBeVisited.erase(toBeVisited.begin() + idx);

  auto neighbors = getVisitedNeighbors(w, current);
  if (neighbors.empty()) return true;

  int nIdx = Random::Range(0, (int)neighbors.size() - 1);
  Point2D neighbor = neighbors[nIdx];

  RemoveWall(w, current, neighbor);

  visitedSet.insert(current);
  w->SetNodeColor(current, Color::Red);
  w->SetNodeColor(neighbor, Color::Red);

  auto vs = getVisitables(w, current);
  toBeVisited.insert(toBeVisited.end(), vs.begin(), vs.end());

  return true;
}

void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  visitedSet.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  std::vector<Point2D> visitables;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  // todo: code this

  auto sideOver2 = w->GetSize() / 2;

  for (auto& d : deltas) {
    Point2D neighbor = p + d;

    if (neighbor.x < -sideOver2 || neighbor.x > sideOver2 ||
        neighbor.y < -sideOver2 || neighbor.y > sideOver2)
      continue;

    if (!visitedSet.count(neighbor)) {
      visitables.push_back(neighbor);
      w->SetNodeColor(neighbor, Color::DarkGray);
    }
  }

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> neighbors;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  // todo: code this

  auto sideOver2 = w->GetSize() / 2;

  for (auto& d : deltas) {
    Point2D neighbor = p + d;

    if (neighbor.x < -sideOver2 || neighbor.x > sideOver2 ||
        neighbor.y < -sideOver2 || neighbor.y > sideOver2)
      continue;

    if (visitedSet.count(neighbor)) {
      neighbors.push_back(neighbor);
    }
  }

  return neighbors;
}
