#ifndef INTERFACE_OUTPUT_H
#define INTERFACE_OUTPUT_H

void rtbtDumpUnstructuredMesh(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType);

#endif
