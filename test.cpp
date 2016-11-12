#include <cassert>
#include <iostream>
#include "geometric_graph.hpp"
#include "shortest_paths.hpp"

using std::vector;

void GeometricGraphTests() {
  // empty graph
  GeometricGraph g(0.5);
  assert(g.Eps() == 0.5);
  assert(g.V() == 0);
  assert(g.E() == 0);

  
  Point2D p(0,0);
  vertex_id v = g.add_vertex(p);
  assert(v == 0);
  assert(g.V() == 1);
  assert(g.E() == 0);
  assert(g.position(v) == p);

  // add a neighboring point
  vertex_id u = g.add_vertex(Point2D(0.1,0.1));
  assert(u == 1);
  assert(g.V() == 2);
  assert(g.E() == 1);

  const vector<HalfEdge> out_edges = g.links(0);
  assert(out_edges.size() == 1);
  HalfEdge out = out_edges[0];
  assert(out.to == u);
  assert(out.weight == 0.1*sqrt(2.0));

  // add an isolated point
  vertex_id w = g.add_vertex(Point2D(1.0,1.0));
  assert(w == 2);
  assert(g.V() == 3);
  assert(g.E() == 1);
  assert(g.links(0).size() == 1);
  assert(g.links(1).size() == 1);
  assert(g.links(2).size() == 0);

  // shrink the graph
  vertex_id w2 = g.add_vertex(Point2D(-0.49,0.0));
  assert(w2 == 3);
  assert(g.links(0).size() == 2);
  assert(g.links(3).size() == 1);
  assert(g.E() == 2);

  g.shrink(0.4);
  assert(g.links(0).size() == 1);
  assert(g.links(3).size() == 0);
  assert(g.E() == 1);

}

void ClosestPointTests() {
  GeometricGraph g(1.0);
  vertex_id u,v,w;

  u = g.add_vertex(Point2D(0,0));
  v = g.add_vertex(Point2D(1,0));
  w = g.add_vertex(Point2D(1,1));

  assert(g.closest(Point2D(0,0)) == u);
  assert(g.closest(Point2D(0.1,0)) == u);
  assert(g.closest(Point2D(1.1,0.9)) == w);

}


void ShortestPathsTests() {
  GeometricGraph g(1.01);
  vertex_id u = g.add_vertex(Point2D(0,0));
  vertex_id v = g.add_vertex(Point2D(1,0));
  vertex_id w = g.add_vertex(Point2D(1,1));

  assert(g.E() == 2);

  ShortestPaths sp(g,u);

  assert(sp.hasPath(u));
  assert(sp.dist(u) == 0.0);
  assert(sp.dist(v) == 1.0);
  assert(sp.dist(w) == 2.0);
};


int main() {
  GeometricGraphTests();
  ClosestPointTests();
  ShortestPathsTests();
  std::cout << "Tests passed!" << std::endl;
  return 0;
}
