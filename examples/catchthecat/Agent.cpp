#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>
#include "World.h"
using namespace std;

//Noted code from professor
//int huristic(Point2D& p, int sideSizeOver2 {
//  return std::min({sideSideOver2 - abs(p.x), sideSizeOver2 - abs(p.y)}) +
// shadowcastingVisibilityFunction(p, sideSizeOver2);

//Huristic
int heuristic(Point2D p, int sideSize) {
  int halfSide = sideSize / 2;
  int dx = halfSide - abs(p.x);
  int dy = halfSide - abs(p.y);
  return std::min(dx, dy);
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  //queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  std::unordered_map<Point2D, int> gScore;   // The best possible path

  struct Node {
    // Open Set
    Point2D pos;
    int g;
    int f;

    bool operator>(const Node& other) const {
      return f > other.f;
    }
  };

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;

  //struct CompareNode {
    // Compares the nodes like in class
  //  bool operator()(const Node& a, const Node& b) const { return a.f > b.f; }
  //};

  // bootstrap state
  auto catPos = w->getCat();
  int worldSize = w->getWorldSideSize();
  gScore[catPos] = 0;
  frontier.push({catPos, 0, heuristic(catPos, worldSize)});

  //frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  // Diagonal Directions
  auto forCube = [](const Point2D& p) {
    int col = p.x;
    int row = p.y;
    int cx = col - (row - (row& 1)) /2;
    int cz = row;
    int cy = -cx - cz;
    return std::tuple<int, int, int> (cx, cy, cz);
  };

  // Deal with the Hexagon
  auto hexDist = [&](const Point2D& a, const Point2D& b) -> int {
    int ax, ay, az, bx, by, bz;
    std::tie(ax, ay, az);
    std::tie(bx, by, bz);
    return std::max({std::abs(ax - bx), std::abs(ay - by), std::abs(az - bz)});
  };

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    Node current = frontier.top();
    frontier.pop();

    // Win if the cat gets to the border
    if (w->isBorder(current.pos)) {
      borderExit = current.pos;
      break;
    }

  for (auto& neighbor : w->getVisitableNeighbors(current.pos)) {
    int cost_gScore = gScore.at(current.pos) + 1;

    // Check for a better path
    if (gScore.find(neighbor) == gScore.end() || cost_gScore < gScore.at(neighbor)) {
      cameFrom[neighbor] = current.pos;
      gScore[neighbor] = cost_gScore;
      int fScore = cost_gScore + heuristic(neighbor, worldSize);
      frontier.push({neighbor, cost_gScore, fScore});
    }
  }

    /* From when I was doing BFS originally
    auto current = frontier.front(); // Next Tile
    frontier.pop(); // Remove from the Queue
    frontierSet.erase(current); // Erase
    visited[current] = true; // Set Visited

    for (auto& neighbor : w->getVisitableNeighbors(current)) {
      if (visited.find(neighbor) == visited.end() && frontierSet.find(neighbor) == frontierSet.end()) {
        cameFrom[neighbor] = current;
        frontier.push(neighbor);
        frontierSet.insert(neighbor);

        if (w->isBorder(neighbor)) {
          borderExit = neighbor;
          frontier = queue<Point2D>(); // Clear Queue
          break;
        }
      }
    }
    */

  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  //return vector<Point2D>();

  vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {
    // Exit
    Point2D current = borderExit;
    while (current != catPos) {
      path.push_back(current);
      current = cameFrom.at(current);
    }
    std::reverse(path.begin(), path.end());
  }

  // Return the path
  return path;
}
