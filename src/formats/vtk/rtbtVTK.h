#ifndef RTBTVTK_H
#define RTBTVTK_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkVoxel.h>
#include <vtkVertex.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkXMLPUnstructuredGridWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDoubleArray.h>
#include <vtkTriangle.h>

using namespace std;

class c_VTK{

public:
    string _fileName;
    int _numNodes;
    int _numNodesPerCell;
    int _numCells;
    double *_x;
    double *_y;
    double *_z;
    int **_cellCon;

    vtkSmartPointer<vtkPoints> _points;
    vtkSmartPointer<vtkVoxel> *_voxel; 
    vtkSmartPointer<vtkCellArray> _cellArray;
    vtkSmartPointer<vtkDoubleArray> *_cellCenterData;
    vtkSmartPointer<vtkUnstructuredGrid> _unstructuredGrid;
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> _writer;
    vtkSmartPointer<vtkXMLPUnstructuredGridWriter> _pwriter;
    
public:
////    c_VTK(const char* _fileName, int num_nodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, float **varMatrix, int mpi_rank, int mpi_size);
//    c_VTK(string _fileName, int num_nodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, vector<string> varNameVec, float **varMatrix, int mpi_rank, int mpi_size);
    c_VTK(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon);
    ~c_VTK();

    void fileCreation();
      void createPoints();
      void createCells();
      void createGrid();
      void writeFile();

//    void createCellCenterData();
//    void createNodalData();
////      const char* getIndividualFileName();
//      string getIndividualFileName();
////      const char* getParallelFileName();
//      string getParallelFileName();
//    void parallelWriteFile();
//

};

#endif
