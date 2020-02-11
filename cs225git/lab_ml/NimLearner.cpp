/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */

 /** 
  *  g_ is both a directed AND weighted graph!!!!
  *  initialized using initializer list.
  **/
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* insert vertices from both sides. */
    for (int i = startingTokens; i >= 0; i--){
      Vertex inserted = "p1-" + std::to_string(i);
      g_.insertVertex(inserted);
    }
    for (int i = startingTokens; i >= 0; i--){
      Vertex inserted = "p2-" + std::to_string(i);
      g_.insertVertex(inserted);
    }
    /* connect the vertices and set the weights of the edges to 0. */
    for (int i = startingTokens; i > 0; i--){
      if (i >= 2){
        g_.insertEdge("p1-"+ std::to_string( i), "p2-"+std::to_string( i-1));
        g_.setEdgeWeight("p1-"+ std::to_string( i), "p2-"+std::to_string( i-1), 0);
        g_.insertEdge("p1-"+ std::to_string( i), "p2-"+std::to_string( i-2));
        g_.setEdgeWeight("p1-"+ std::to_string( i), "p2-"+std::to_string( i-2), 0);
      }
      if (i == 1){
        g_.insertEdge("p1-"+ std::to_string( i), "p2-"+std::to_string(i-1));
        g_.setEdgeWeight("p1-"+ std::to_string( i), "p2-"+std::to_string(i-1), 0);
      }
    }

    for (int i = startingTokens; i > 0; i--){
      if (i >= 2){
        g_.insertEdge("p2-"+ std::to_string( i), "p1-"+std::to_string(i-1));
        g_.setEdgeWeight("p2-"+ std::to_string(i), "p1-"+std::to_string(i-1), 0);
        g_.insertEdge("p2-"+ std::to_string( i), "p1-"+std::to_string(i-2));
        g_.setEdgeWeight("p2-"+ std::to_string( i), "p1-"+std::to_string(i-2), 0);
      }
      if (i == 1){
        g_.insertEdge("p2-"+ std::to_string( i), "p1-"+std::to_string(i-1));
        g_.setEdgeWeight("p2-"+ std::to_string( i), "p1-"+std::to_string(i-1), 0);
      }
    }

    /* set startingVertex to p1-startingTokens. Useful for the next fn. */
    startingVertex_ = "p1-" + std::to_string((int) startingTokens);
    num_of_tokens = (int) startingTokens;
    /* Done! */
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* I love my girl. */
  Vertex current_vertex = startingVertex_;
  std::vector<Edge> some_vec = g_.getEdges();
  while (current_vertex != "p1-0" && current_vertex != "p2-0"){
    int some_number = rand() % (int) some_vec.size();
    Edge some_edge = some_vec[some_number];
    if (some_edge.source != current_vertex) continue;
    /** edge between these two points exists.
     * update current_vertex and pop this edge. 
     **/
    path.push_back(some_edge);
    current_vertex = some_edge.dest;
    std::swap(some_vec[some_number], some_vec[some_vec.size()-1]);
    some_vec.pop_back();
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  /* I love my girl. */
  std::vector<Edge> some_path = path;
  /* determine which player actually won the game. */
  Vertex last_vertex = some_path[some_path.size()-1].dest;
  if (last_vertex == "p1-0"){
    /* punish player 1 and reward player 2. */
    for (const auto &e : some_path){
      if (e.source[1] == '2') g_.setEdgeWeight(e.source, e.dest, e.getWeight()+1);
      if (e.source[1] == '1') g_.setEdgeWeight(e.source, e.dest, e.getWeight()-1);
    }
  }
  else if (last_vertex == "p2-0"){
    /* punish player 2 and reward player 1. */
    for (const auto &e : some_path){
      if (e.source[1] == '1') g_.setEdgeWeight(e.source, e.dest, e.getWeight()+1);
      if (e.source[1] == '2') g_.setEdgeWeight(e.source, e.dest, e.getWeight()-1);
    }
  }
  return;
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
