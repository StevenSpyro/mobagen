#include "HuntAndKillExample.h"
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

bool HuntAndKillExample::Step(World* w) {
  // todo: code this
  auto sideOver2 = w->GetSize() / 2;

  // Initialize on first call
  if (!initialized) {
    initialized = true;
    Point2D start = randomStartPoint(w);
    if (start.x == INT_MAX) return false;

    current = start;
    visited[current.y][current.x] = true;
    w->SetNodeColor(current, Color::Red);
  }

  // Phase 1: Random walk until dead end
  auto visitables = getVisitables(w, current);
  if (!visitables.empty()) {
    // Choose a random unvisited neighbor
    Point2D next = visitables[Random::Range(0, (int)visitables.size() - 1)];

    // Remove wall between current and next
    RemoveWall(w, current, next);

    // Mark next as visited
    visited[next.y][next.x] = true;
    w->SetNodeColor(next, Color::Green);   // newly carved
    w->SetNodeColor(current, Color::Red);  // just carved

    current = next;
    return true;
  }

  // Phase 2: Hunt for unvisited cell with visited neighbor
  for (int y = -sideOver2; y <= sideOver2; y++) {
    for (int x = -sideOver2; x <= sideOver2; x++) {
      if (!visited[y][x]) {
        Point2D candidate{x, y};
        auto neighbors = getVisitedNeighbors(w, candidate);
        if (!neighbors.empty()) {
          // Found the next start point
          Point2D neighbor = neighbors[Random::Range(0, (int)neighbors.size() - 1)];

          RemoveWall(w, candidate, neighbor);

          visited[candidate.y][candidate.x] = true;
          w->SetNodeColor(candidate, Color::Green);
          w->SetNodeColor(neighbor, Color::Red);

          current = candidate;
          return true;
        }
      }
    }
  }

  // No unvisited cells remain
  return false;
}

void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  initialized = false;
  current = {INT_MAX, INT_MAX};

  int sideOver2 = world->GetSize() / 2;
  for (int y = -sideOver2; y <= sideOver2; y++) {
    visited[y].clear();
    for (int x = -sideOver2; x <= sideOver2; x++) {
      visited[y][x] = false;
    }
  }
}

Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++) {
    for (int x = -sideOver2; x <= sideOver2; x++) {
      if (!visited[y][x]) return {x, y};
    }
  }
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  std::vector<Point2D> visitables;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::RIGHT, Point2D::DOWN, Point2D::LEFT};
  auto sideOver2 = w->GetSize() / 2;
  // todo: code this

  for (auto& d : deltas) {
    Point2D neighbor = p + d;

    if (neighbor.x < -sideOver2 || neighbor.x > sideOver2 ||
        neighbor.y < -sideOver2 || neighbor.y > sideOver2)
      continue;

    if (!visited[neighbor.y][neighbor.x]) {
      visitables.push_back(neighbor);
      w->SetNodeColor(neighbor, Color::DarkGray);
    }
  }

  return visitables;
}

std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> neighbors;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::RIGHT, Point2D::DOWN, Point2D::LEFT};
  auto sideOver2 = w->GetSize() / 2;
  // todo: code this

  for (auto& d : deltas) {
    Point2D neighbor = p + d;

    if (neighbor.x < -sideOver2 || neighbor.x > sideOver2 ||
        neighbor.y < -sideOver2 || neighbor.y > sideOver2)
      continue;

    if (visited[neighbor.y][neighbor.x]) {
      neighbors.push_back(neighbor);
    }
  }

  return neighbors;
}
