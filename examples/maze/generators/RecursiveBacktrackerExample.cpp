#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

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

bool RecursiveBacktrackerExample::Step(World* w) {
    auto sideOver2 = w->GetSize() / 2;

    if (stack.empty()) {
        Point2D start = randomStartPoint(w);
        if (start.x == INT_MAX) return false;
        stack.push_back(start);
        visited[start.y][start.x] = true;
        w->SetNodeColor(start, Color::DarkRed); // Color
    }

    if (stack.empty()) return false;

    Point2D current = stack.back();

    std::vector<Point2D> visitables = getVisitables(w, current);

    if (!visitables.empty()) {
        // Next
        Point2D next;
        if (visitables.size() == 1) next = visitables[0];
        else next = visitables[Random::next() % visitables.size()];

        RemoveWall(w, current, next);

        visited[next.y][next.x] = true;
        w->SetNodeColor(next, Color::Green); // New Cell

        w->SetNodeColor(current, Color::Red); // Old Cell

        stack.push_back(next);
    }
    else {
        // Backtracking: current cell done
        w->SetNodeColor(current, Color::Black);
        stack.pop_back();

        if (!stack.empty()) {
            // New top of stack is now current
            w->SetNodeColor(stack.back(), Color::Red);
        }
    }

    return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
    visited.clear();
    stack.clear();

    int sideOver2 = world->GetSize() / 2;
    for (int y = -sideOver2; y <= sideOver2; y++) {
        visited[y].clear();
        for (int x = -sideOver2; x <= sideOver2; x++) {
            visited[y][x] = false;
        }
    }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
    auto sideOver2 = world->GetSize() / 2;
    for (int y = -sideOver2; y <= sideOver2; y++) {
        for (int x = -sideOver2; x <= sideOver2; x++) {
            if (!visited[y][x]) return {x, y};
        }
    }
    return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
    std::vector<Point2D> visitables;
    std::vector<Point2D> deltas = {Point2D::UP, Point2D::RIGHT, Point2D::DOWN, Point2D::LEFT};
    auto sideOver2 = w->GetSize() / 2;

    for (auto& d : deltas) {
        Point2D neighbor = p + d;

        // Bounds check
        if (neighbor.x < -sideOver2 || neighbor.x > sideOver2 || neighbor.y < -sideOver2 || neighbor.y > sideOver2)
            continue;

        if (!visited[neighbor.y][neighbor.x]) {
            visitables.push_back(neighbor);
            w->SetNodeColor(neighbor, Color::DarkGray); // Color
        }
    }

    return visitables;
}
