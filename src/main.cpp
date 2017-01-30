#include "main.h"

int pavlov_createUnstructuredMesh(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType){

     cout << " Rotorbit PAVLOV function has been initiated." << '\n';

//     liberOutVector(fileName, gridName, gridType, topoType, cellNum, nodePerCell, nodeNum, numberOfVarName, vtkStringVec, AMR->cellData, AMR->x, AMR->y, AMR->z,cells, info, comm);

     rtbtDumpUnstructuredMesh(fileName, numNodes, numNodesPerCell, numCells, x, y, z, cellCon, fileType);
//     rtbtDumpUnstructuredMesh(fileName, nodeNum, nodePerCell, cellNum, x, y, z, cells);

     cout << " Rotorbit PAVLOV function has been finished." << '\n';

}

int pavlov_createUnstructuredMeshWithField(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType){

    


}
