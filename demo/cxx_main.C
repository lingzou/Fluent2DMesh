#include <iostream>
#include <sstream>      //std::ostringstream

#include "../FluentTwoDMesh.h"

int main(int argc, char **argv)
{
  FluentTwoDMesh * p_mesh = new FluentTwoDMesh();
  bool quite = false;
  bool debug = false;
  //p_mesh->createMeshFromFile("flow-past-a-cylinder.msh", quite, debug);
  p_mesh->createMeshFromFile("cavity.msh", quite, debug);

  // Let's see what we have in the FluentTwoDMesh
  std::cout << "# of faces: " << p_mesh->n_Faces() << std::endl;

  std::vector<Node*> & node_set = p_mesh->getNodeSet();
  std::map<int, std::vector<Face*> > & face_zone_map = p_mesh->getFaceZoneMap();
  std::vector<FluentTriCell> & cell_set = p_mesh->getCellSet();

  std::cout << "Number of nodes = " << node_set.size() << std::endl;
  //for (long int i = 0; i < node_set.size(); i++)
  //{
  //  std::cout << node_set[i]->id() << " " << "(x = " << node_set[i]->x() << ", y = " << node_set[i]->y() << ", z = " << node_set[i]->z() << ")" << std::endl;
  //}

  std::cout << "Number of cells = " << cell_set.size() << std::endl;

  for (std::map<int, std::vector<Face*> >::iterator it = face_zone_map.begin(); it != face_zone_map.end(); ++it)
  {
    long int zone_id = it->first;
    std::vector<Face*> & faces = it->second;

    std::cout << "Face Zone " << zone_id << std::endl;
    std::cout << "   number of faces = " << faces.size() << std::endl;
  }

  /*
  FluentTriCell & cell_start = cell_set[0];
  cell_start.mark_cell_and_its_neighbor_cells();
  */
  /*
  Node * node0 = node_set[0];
  std::cout << "node0 id = " << node0->id() << std::endl;
  node0->mark_node_and_its_neighbor_nodes();
  */

  // Let's write some data into a VTU file
  FILE * ptr_File;
  ptr_File = fopen("output.vtu", "w");
  p_mesh->writeMesh(ptr_File);
  std::ostringstream out_string_stream;

  // ----> CellData Begins
  out_string_stream << "      <CellData>" << "\n";
  // CELL DATA (cell ID)
  out_string_stream << "        <DataArray type=\"Float32\" Name=\"Cell_ID\" format=\"ascii\">" << "\n";
  for(unsigned int i = 0; i < cell_set.size(); i++)
    out_string_stream << "          " << cell_set[i].id() << "\n";
  out_string_stream << "        </DataArray>" << "\n";
  // CELL DATA (volume)
  out_string_stream << "        <DataArray type=\"Float32\" Name=\"volume\" format=\"ascii\">" << "\n";
  for(unsigned int i = 0; i < cell_set.size(); i++)
    out_string_stream << "          " << cell_set[i].volume() << "\n";
  out_string_stream << "        </DataArray>" << "\n";
  // T = sin(2 pi x) * cos(pi x)
  out_string_stream << "        <DataArray type=\"Float32\" Name=\"temperature\" format=\"ascii\">" << "\n";
  for(unsigned int i = 0; i < cell_set.size(); i++)
  {
    double x = cell_set[i].centroid().x(); double y = cell_set[i].centroid().y();
    out_string_stream << "          " << sin(2.0 * 3.14159265 * x) * cos(3.14159265 * y) << "\n";
  }
  out_string_stream << "        </DataArray>" << "\n";
  out_string_stream << "      </CellData>" << "\n";
  // ----> CellData ends

  // POINT DATA Begins
  out_string_stream << "      <PointData>" << "\n";
  // NODE ID
  out_string_stream << "        <DataArray type=\"Float32\" Name=\"Node_ID\" format=\"ascii\">" << "\n";
  for(unsigned int i = 0; i < node_set.size(); i++)
    out_string_stream << "          " << node_set[i]->id() << "\n";
  out_string_stream << "        </DataArray>" << "\n";
  // phi = sin(pi x) * cos(pi x)
  out_string_stream << "        <DataArray type=\"Float32\" Name=\"phi\" format=\"ascii\">" << "\n";
  for(unsigned int i = 0; i < node_set.size(); i++)
  {
    double x = node_set[i]->x(); double y = node_set[i]->y();
    out_string_stream << "          " << sin(3.14159265 * x) * cos(3.14159265 * y) << "\n";
  }
  out_string_stream << "        </DataArray>" << "\n";

  out_string_stream << "      </PointData>" << "\n";
  // POINT DATA ends

  fprintf(ptr_File, "%s", out_string_stream.str().c_str());

  p_mesh->finishFile(ptr_File);
  fclose(ptr_File);

  // Always remember to delete your mesh
  delete p_mesh;

  return 0;
}
