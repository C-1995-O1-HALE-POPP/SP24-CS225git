/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"


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
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {
  //vertex
  for (unsigned i = 0; i <=startingTokens; i++) {
    g_.insertVertex("p1-" + std::to_string(i));
    g_.insertVertex("p2-" + std::to_string(i));
  }

  //edge
  for (unsigned i = startingTokens; i >=2; i--) {
    Vertex p1=g_.getVertexByLabel("p1-"+std::to_string(i));
    Vertex p2=g_.getVertexByLabel("p2-"+std::to_string(i));
    Vertex p1_1=g_.getVertexByLabel("p1-"+std::to_string(i-1));
    Vertex p2_1=g_.getVertexByLabel("p2-"+std::to_string(i-1));
    Vertex p1_2=g_.getVertexByLabel("p1-"+std::to_string(i-2));
    Vertex p2_2=g_.getVertexByLabel("p2-"+std::to_string(i-2));
    g_.insertEdge(p1,p2_1);
    g_.insertEdge(p2,p1_1);
    g_.insertEdge(p1,p2_2);
    g_.insertEdge(p2,p1_2);
    g_.setEdgeWeight(p1,p2_1,0);
    g_.setEdgeWeight(p2,p1_1,0);
    g_.setEdgeWeight(p1,p2_2,0);
    g_.setEdgeWeight(p2,p1_2,0);
  }
  Vertex p1_1=g_.getVertexByLabel("p1-1");
  Vertex p2_1=g_.getVertexByLabel("p2-1");
  Vertex p1_0=g_.getVertexByLabel("p1-0");
  Vertex p2_0=g_.getVertexByLabel("p2-0");
  g_.insertEdge(p1_1,p2_0);
  g_.insertEdge(p2_1,p1_0);
  g_.setEdgeWeight(p1_1,p2_0,0);
  g_.setEdgeWeight(p2_1,p1_0,0);

  startingVertex_=g_.getVertexByLabel("p1-"+std::to_string(startingTokens));
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
  Vertex cur=startingVertex_;
  Vertex p1_0=g_.getVertexByLabel("p1-0");
  Vertex p2_0=g_.getVertexByLabel("p2-0");

  while(cur!=p2_0 && cur!=p1_0){
    vector<Vertex> adj=g_.getAdjacent(cur);
    Vertex next=adj[rand()%adj.size()];
    path.push_back(g_.getEdge(cur,next));
    cur=next;
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
  if(g_.getVertexLabel(path[path.size()-1].dest)=="p1-0"){          // P2 win
    for(unsigned i=0;i<path.size();i++){
      if(i%2==0){
        int weight=g_.getEdgeWeight(path[i].source,path[i].dest);
        g_.setEdgeWeight(path[i].source,path[i].dest,weight-1);
      }else{
        int weight=g_.getEdgeWeight(path[i].source,path[i].dest);
        g_.setEdgeWeight(path[i].source,path[i].dest,weight+1);      
      }
    }
  }
  if(g_.getVertexLabel(path[path.size()-1].dest)=="p2-0"){          // P1 win
    for(unsigned i=0;i<path.size();i++){
      if(i%2==0){
        int weight=g_.getEdgeWeight(path[i].source,path[i].dest);
        g_.setEdgeWeight(path[i].source,path[i].dest,weight+1);
      }else{
        int weight=g_.getEdgeWeight(path[i].source,path[i].dest);
        g_.setEdgeWeight(path[i].source,path[i].dest,weight-1);      
      }
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
