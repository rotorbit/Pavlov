#include "def_output.h"

using namespace std;

//void liberOut(string fileName, char* gridName, char* gridType, char* topoName,int cellNum, int nodePerCell, int nodeNum, int varSize, char** varName, char** varType, float** varMatrix, float *x, float *y, float *z, int** cellConMatrix,  MPI_Info &info,  MPI_Comm &comm){
//
////Output *output1=NULL;
////output1 = new Output();
////
////////// set all the input parameters correctly
////output1->setNames(fileName,gridName, gridType,topoName);
////output1->setGeometryValues(cellNum,nodePerCell,nodeNum,x, y, z, cellConMatrix);
////output1->setVariables(varSize, varName, varType, varMatrix);
//////
////output1->parSetParameters(info, comm);
////output1->createVTKObject();
////////// write out output file
////
////delete output1;
//
//}
//
//void liberOutVector(string fileName, char* gridName, char* gridType, char* topoName,int cellNum, int nodePerCell, int nodeNum, int varSize, vector<string> varNameVec, float** varMatrix, float *x, float *y, float *z, int** cellConMatrix,  MPI_Info &info,  MPI_Comm &comm){
//
//Output *output1=NULL;
//output1 = new Output();
//
//////// set all the input parameters correctly
//output1->setNames(fileName,gridName, gridType,topoName);
//output1->setGeometryValues(cellNum,nodePerCell,nodeNum,x, y, z, cellConMatrix);
//output1->setVariables(varSize, varNameVec, varMatrix);
////
//output1->parSetParameters(info, comm);
//output1->createVTKObject();
//////// write out output file
//
//delete output1;
//
//
//
//}
//
//
//Output::~Output(){
//
////  delete [] _varName;
////  delete [] _varType;
////  delete [] _varLength;
//  delete [] _varMatrix;
//  delete [] _cellConMatrix;
//
//}
//
//void Output::parSetParameters(MPI_Info &info,  MPI_Comm &comm){
//
//     _info = info;
//     _comm = comm;
//
//}
//
void c_Output::setFileName(string fileName){

    _fileName=fileName;

}

void c_Output::setMeshParameters(int numNodes, int numNodesPerCell, int numCells){

    _numNodes = numNodes;  
    _numNodesPerCell = numNodesPerCell;
    _numCells = numCells;

}

void c_Output::setNodeXYZPositions(double *x, double *y, double *z){

    _x = x;
    _y = y;
    _z = z;

}

void c_Output::setCellConnectivity(int **cellCon){

    _cellCon = cellCon;

}

void c_Output::setFileType(string fileType){

    _fileType = fileType;

}

void c_Output::createCorrespondingFile(){

    if(_fileType == "VTK"){
      VTK = NULL;
      VTK = new c_VTK(_fileName, _numNodes, _numNodesPerCell, _numCells, _x, _y, _z, _cellCon);
      VTK->fileCreation();
      cout << "  VTK type file is created." << '\n';
    }

}

////void Output::setVariables( int varSize, char** varName, char** varType, float** varMatrix){
//void Output::setVariables( int varSize, vector<string> varNameVec, float** varMatrix){
//
//  _varSize=varSize;
//  _varNameVec=varNameVec;
////  _varName = new char*[_varSize]; 
////  _varType = new char*[_varSize]; 
////  _varLength = new int[_varSize]; 
//    _temp_varMatrix = varMatrix; 
////  _varMatrix = new float*[_varSize];
//
////  for(int i=0; i<_varSize;i++){
////    _varName[i]=varName[i];
////    _varType[i]=varType[i];
////    _varMatrix[i]=varMatrix[i];
////    if(strcmp(_varType[i],"Cell")==0){
////      _varLength[i] = _cellNum;
////    }
////    else if(strcmp(_varType[i],"Node")==0){
////      _varLength[i] = _nodeNum;
////    }
////  }
//
//}
//
//void Output::_2DMatrixto1DArray(int **cellConMatrix){
//
//   _cellConMatrix = new int [_cellNum*_nodePerCell];
//
//   for(int i =0; i<_cellNum; i++){
//     for(int j =0; j<_nodePerCell; j++){
//       _cellConMatrix[i*_nodePerCell+j] = cellConMatrix[i][j];
//     }
//   }
//
//}
//
//void Output::setGeometryValues(int cellNum, int nodePerCell, int nodeNum, float *x, float *y, float *z, int **cellConMatrix){
//  _cellNum=cellNum;
//  _nodePerCell=nodePerCell;
//  _nodeNum=nodeNum;
//  _x = x;
//  _y = y;
//  _z = z;
//
//  _2DMatrixto1DArray(cellConMatrix);
//  _actualCellConMatrix = cellConMatrix ;
//
//}
//
//void Output::createVTKObject(){
//
//    int local_mpi_rank;
//    int local_mpi_size;
//    MPI_Comm_rank(_comm, &local_mpi_rank);
//    MPI_Comm_size(_comm, &local_mpi_size);
//    VTK = new c_VTK(_fileName, _nodeNum, _x, _y, _z, _cellNum, _nodePerCell, _actualCellConMatrix, _varSize, _varNameVec, _temp_varMatrix, local_mpi_rank, local_mpi_size);
//    VTK->fileCreation();
//
//}
