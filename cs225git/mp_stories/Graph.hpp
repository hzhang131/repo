#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  unsigned int num_vertices = vertexMap.size();
  return num_vertices;
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  // first calculate the out-degrees by lookup the map.
    auto lst = adjList.at(v.key());
    return lst.size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  //Add another vertex in vertexMap.
  vertexMap.insert({key, v});
  //Add another vertex in AdjList.
  std::list<edgeListIter> temp;
  adjList.insert({key, temp});
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  
  for (const auto& it: adjList[key]){
    auto obj = it -> get();
    std::string s = (obj.source().key() == key? (obj.dest()).key() : (obj.source()).key());
    adjList[s].remove(it);
    edgeList.erase(it);
  }
  // after removing every edge associated, we may remove the vertex from the vertexMap.
  vertexMap.erase(key);
  adjList.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  // easier operation, put it into the edge list.
  edgeList.push_front(e);
  // harder operation, update the adjacency list.
  edgeListIter edge_it = edgeList.begin();
  adjList.at(v1.key()).push_front(edge_it); 
  adjList.at(v2.key()).push_front(edge_it); 
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  // find the exact edge from the edgeList.
  for (auto it = edgeList.begin(); it != edgeList.end(); ++it){
    if (((*it).get().source().key() == key1) && ((*it).get().dest().key() == key2)){
      removeEdge(it);
      break;
    }
  }
  return;
}

/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  // That is the boy hahaha.
  // Inb4 we remove the edge from the edge list, we need to figure out the source/ des vertex.
  auto& src = (*it).get().source();
  auto& des = (*it).get().dest();
  auto& lst_src = adjList.at(src.key());
  auto lst_src_iter = lst_src.begin();
  auto& lst_des = adjList.at(des.key());
  auto lst_des_iter = lst_des.begin();
  lst_src.remove(it);
  lst_des.remove(it);
  edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  //get all edges from adjacency list.
  for (const auto& edge_it :adjList.at(key)){
    edges.push_front((*edge_it));
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  auto lst = incidentEdges(key1);
  for (const auto& edge: lst){
    if ((edge.get().directed() == false) && (edge.get().source().key() == key2) && (edge.get().dest().key() == key1)){
      return true;
    }
    if ((edge.get().source().key() == key1) && (edge.get().dest().key() == key2)){
      return true;
    }
  }
  return false;
}
