#ifndef DEF_OUTPUT_H
#define DEF_OUTPUT_H

#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

#include "../formats/vtk/rtbtVTK.h"

using namespace std;

class c_Output{
  /*!This is Output class

  */
///*! SetVariables: smth stmh */
//    void setVariables(int, vector<string>, float**);
//    void setGeometryValues(int,int,int, float*, float*, float*, int**);   
//
//    void parSetParameters(MPI_Info &,  MPI_Comm &);
//
//    void createVTKObject();
//    void parWriteVTK();
//    void writePVTU();
////Constructor deconstrutor
//    ~Output();  
//  private:
//    //methods
//    void _2DMatrixto1DArray(int**);

    //data
    string _fileName;// = NULL; 
    int _numNodes;
    int _numNodesPerCell;
    int _numCells;
    double *_x, *_y, *_z;
    int **_cellCon;
    string _fileType;
    c_VTK *VTK;

//    char *_gridName;// = NULL; 
//    char *_gridType;// = NULL;
//    char *_topoType;// = NULL;

//    int **_actualCellConMatrix;
//    int _varSize;
//    vector<string>  _varNameVec;// = NULL;
//    char **_varType;// = NULL;
//    int *_varLength;
//    float **_varMatrix;
//    float **_temp_varMatrix;

   public:
    void setFileName(string);
    void setMeshParameters(int, int, int);
    void setNodeXYZPositions(double *, double *, double *);
    void setCellConnectivity(int **);
    void setFileType(string);
    void createCorrespondingFile();

}; 

#endif
