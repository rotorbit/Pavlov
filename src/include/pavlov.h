#include <iostream>
#include <string>

using namespace std;

//int pavlov_OutputResults(string fileName, double *x, double *y, double *z, int ** cellCon);

int pavlov_createUnstructuredMesh(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType);

int pavlov_createUnstructuredMeshWithField(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType);
