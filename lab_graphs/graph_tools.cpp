/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    initGraph(graph);
    int minWeight = INT_MAX;
    Vertex min_u, min_v;

    Vertex v=graph.getStartingVertex();
    queue<Vertex> q;
    graph.setVertexLabel(v,"VISITED");
    q.push(v);
    while(!q.empty()){
        Vertex u=q.front();
        q.pop();
        vector<Vertex> adj=graph.getAdjacent(u);
        for(auto& v : adj){
            if(graph.getVertexLabel(v)=="UNEXPLORED"){
                graph.setEdgeLabel(u,v,"DISCOVERY");
                graph.setVertexLabel(v,"VISITED");
                q.push(v);
            }else if(graph.getEdgeLabel(u,v)=="UNEXPLORED"){
                graph.setEdgeLabel(u,v,"CROSS");
            }
            if(graph.getEdgeWeight(u,v)<=minWeight){
                minWeight=graph.getEdgeWeight(u,v);
                min_u=u;
                min_v=v;
            }
        }
    }
    graph.setEdgeLabel(min_u,min_v,"MIN");
    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    //return -1;
    unordered_map<Vertex,Vertex> history;
    initGraph(graph);

    //Vertex v=graph.getStartingVertex();
    queue<Vertex> q;
    graph.setVertexLabel(start,"VISITED");
    q.push(start);
    while(!q.empty()){
        Vertex u=q.front();
        q.pop();
        vector<Vertex> adj=graph.getAdjacent(u);
        for(auto& v : adj){
            if(graph.getVertexLabel(v)=="UNEXPLORED"){
                graph.setVertexLabel(v,"VISITED");
                graph.setEdgeLabel(u,v,"DISCOVERY");
                history[v]=u;
                q.push(v);
            }else if(graph.getEdgeLabel(u,v)=="UNEXPLORED"){
                graph.setEdgeLabel(u,v,"CROSS");
            }
        }
    }

    Vertex curr=end;
    int i=0;
    while(curr!=start){
        graph.setEdgeLabel(curr,history[curr],"MINPATH");
        curr=history[curr];
        i++;
    }
    return i;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges=graph.getEdges();
    vector<Vertex> vertexs=graph.getVertices();
    std::sort(edges.begin(), edges.end(),sortEdge);
    dsets set(vertexs.size());
    size_t numEdges=0;
    while(numEdges<vertexs.size()-1){
        Edge e=edges[0];
        edges.erase(edges.begin());
        Vertex u=e.source;
        Vertex v=e.dest;
        if(set.find(u)!=set.find(v)){
            graph.setEdgeLabel(u,v,"MST");
            set.setunion(set.find(u),set.find(v));
            numEdges++;
        }
    }

    
}
void GraphTools::initGraph(Graph& graph){
    Vertex v=graph.getStartingVertex();
    queue<Vertex> q;
    graph.setVertexLabel(v,"UNEXPLORED");
    q.push(v);
    while(!q.empty()){
        Vertex u=q.front();
        q.pop();
        vector<Vertex> adj=graph.getAdjacent(u);
        for(auto& v : adj){
            if(graph.getEdgeLabel(v,u)!="UNEXPLORED") 
                graph.setEdgeLabel(v,u,"UNEXPLORED");
            if(graph.getVertexLabel(v)!="UNEXPLORED") {
                graph.setVertexLabel(v,"UNEXPLORED");
                q.push(v);
            }
        }
    }
}
bool GraphTools::sortEdge(Edge a, Edge b) {
    return (a.weight<b.weight);
}