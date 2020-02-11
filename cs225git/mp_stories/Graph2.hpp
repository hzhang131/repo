#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <stack>
/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::unordered_map<std::string, bool> visited;
  // distance to the origin "start". 
  std::unordered_map<std::string, int> dist;
  // documenting the vertex before.
  std::unordered_map<std::string, std::string> prev;
  std::queue<std::string> q;
  //load all points to false.
  for (const auto&p: vertexMap){
    visited[p.first] = false;
    dist[p.first] = INT_MAX;
    prev[p.first] = " None ";
  }
  //set the start point as visited.
  visited[start] = true;
  q.push(start);
  prev[start] = " Start ";
  dist[start] = 0;
  while (!q.empty()){
    std::string first = q.front();
    q.pop();
    auto edges = incidentEdges(first);
    int dist_ = dist[first];
    //loop thru all edges. 
    for (const auto& e: edges){
      if (e.get().source().key() == first){
        if (visited.at(e.get().dest().key()) == false){
          visited[e.get().dest().key()] = true;
          q.push(e.get().dest().key());
          dist[e.get().dest().key()] = dist_ + 1;
          prev[e.get().dest().key()] = first;
        }
      }
      else if (e.get().dest().key() == first){
        if (visited.at(e.get().source().key()) == false){
          visited[e.get().source().key()] = true;
          q.push(e.get().source().key());
          dist[e.get().source().key()] = dist_ + 1;
          prev[e.get().source().key()] = first;
        }
      }
    }
    if (first == end) break;
  }
  //translate to path.
  std::stack<std::string> s;
  s.push(end);
  std::string current = prev[end];
  while (current != " Start "){
    s.push(current);
    current = prev[current];
  }
  while (!s.empty()){
    std::string popped = s.top();
    s.pop();
    path.push_back(popped);
  }
  return path;
}

