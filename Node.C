#include "Node.h"

void
Node::mark_node_and_its_neighbor_nodes()
{
  if (!_is_marked)
  {
    _is_marked = true;
    std::cout << id() << " marked." << std::endl;
    /*std::cout << "_connected_faces.size() = " << _connected_faces.size() << std::endl;
    for (unsigned int i = 0; i < _connected_faces.size(); i++)
    {
      std::cout << "  face id = " << _connected_faces[i]->id() << std::endl;
    }*/
    for (unsigned int i = 0; i < _connected_faces.size(); i++)
    {
      //std::cout << "connected face id = " << _connected_faces[i]->id() << std::endl;
      long int neighbor_node_id = _connected_faces[i]->neighbor_node_id(id());
      //std::cout << "neighbor_node_id = " << neighbor_node_id << std::endl;
      Node * nb_Node = (_ptr_mesh->getNodeSet()).at(neighbor_node_id-1);
      if (!nb_Node->isMarked())
        nb_Node->mark_node_and_its_neighbor_nodes();
    }
  }
}
