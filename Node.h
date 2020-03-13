//
//  Node.h
//
//
//  Created by Ling Zou on 5/27/13.
//
//

#ifndef _Node_h
#define _Node_h

#include "Point.h"
#include "FluentTwoDMesh.h"

class Face;
class FluentTwoDMesh;

class Node
{
public:
  // FIXME: consturct without id given?
  Node(Point p) :
    _point(p),
    _id(-1) // an invalid id to initialize
  {
    _connected_faces.clear();
  }

  Node(double x, double y, double z)
  {
    _point.x() = x;
    _point.y() = y;
    _point.z() = z;
  }

  const long int id() const { return _id; }
  long int& id() { return _id; }

  inline const Point & point() const { return _point; }

  const double x() const { return _point.x(); }
  const double y() const { return _point.y(); }
  const double z() const { return _point.z(); }

  void addConnectedFace(Face * face) { _connected_faces.push_back(face); }
  std::vector<Face*> & getConnectedFace() { return _connected_faces; }

  void setParentMesh(FluentTwoDMesh * ptr) { _ptr_mesh = ptr; }
  bool isMarked() { return _is_marked; }
  void mark_node_and_its_neighbor_nodes();

protected:
  Point _point;
  long int _id;

  std::vector<Face*> _connected_faces;
  bool _is_marked;
  FluentTwoDMesh * _ptr_mesh;
};


#endif
