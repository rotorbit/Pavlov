#include "rtbtVTK.h"

//c_VTK::c_VTK(const char* fileName, int num_nodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, float **varMatrix, int mpi_rank, int mpi_size){
//c_VTK::c_VTK(string fileName, int numNodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, vector<string> varNameVec, float **varMatrix, int mpi_rank, int mpi_size){
c_VTK::c_VTK(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon){

    _fileName= fileName;
//  Related to Points
    _numNodes = numNodes;
    _x = new double[_numNodes];
    _y = new double[_numNodes];
    _z = new double[_numNodes];
    for(int i=0; i<_numNodes; i++){
      _x[i] = x[i];
      _y[i] = y[i];
      _z[i] = z[i];
    }
//  Related to Cells
    _numCells = numCells;
    _numNodesPerCell = numNodesPerCell;

    _cellCon = new int *[_numCells];
    for(int i=0; i<_numCells; i++){
     _cellCon[i] = new int[_numNodesPerCell];
    }
    for(int i=0; i<_numCells; i++){
      for(int j=0; j<_numNodesPerCell; j++){
        _cellCon[i][j] = cellCon[i][j];
      }
    }

}

c_VTK::~c_VTK(){
  
//    delete [] _x;
//    _x = NULL;
//
//    delete [] _y;
//    _y = NULL;
//
//    delete [] _z;
//    _z = NULL;
//
//    for(int i=0; i<_num_cells; i++){
//        delete []  _cellConnectivity[i];
//        _cellConnectivity[i] = NULL;
//    }
//    delete [] _cellConnectivity;
//    _cellConnectivity = NULL;
//
////    delete [] _varName;
////    _varName = NULL;
//
//    for(int i=0; i<_varSize; i++){
//        delete []  _varMatrix[i];
//        _varMatrix[i] = NULL;
//    }
//    delete [] _varMatrix;
//    _varMatrix = NULL;

}

void c_VTK::createPoints(){

    _points = vtkSmartPointer<vtkPoints>::New();
    for(int i=0; i<_numNodes; i++){
       _points->InsertNextPoint(_x[i], _y[i], _z[i]);
    }

}

void c_VTK::createCells(){

//  Allocate Cells
    _voxel = new vtkSmartPointer<vtkVoxel>[_numCells];
    for(int i=0; i<_numCells; i++){
      _voxel[i] = vtkSmartPointer<vtkVoxel>::New();
    }

    for(int i=0; i<_numCells; i++){
      for(int j=0; j<_numNodesPerCell; j++){
        _voxel[i]->GetPointIds()->SetId(j, _cellCon[i][j]);
      }
    }

    _cellArray = vtkSmartPointer<vtkCellArray>::New();
    for(int i=0; i<_numCells; i++){
      _cellArray->InsertNextCell(_voxel[i]);
    }

}

//void c_VTK::createCellCenterData(){
//
//    for(int i=0; i<_varSize; i++){
//      _cellCenterData[i] = vtkSmartPointer<vtkDoubleArray>::New();
//    }
//
//    int intCounter=0;
//    for(vector<string>::const_iterator i = _varNameVec.begin(); i != _varNameVec.end(); ++i) {
//      _cellCenterData[intCounter]->SetName((*i).c_str());
//      _cellCenterData[intCounter]->SetNumberOfComponents(1);
//      _cellCenterData[intCounter]->SetNumberOfValues(_num_cells);
//      for(int j=0; j<_num_cells; j++){
//          _cellCenterData[intCounter]->SetValue(j,_varMatrix[intCounter][j]);
//      }
//      intCounter++;
//    }
//
////    for(int i=0; i<_varSize; i++){
//////      _cellCenterData[i]->SetName(_varName[i]);
//////      _cellCenterData[i]->SetName("casey");
////      _cellCenterData[i]->SetNumberOfComponents(1);
////      _cellCenterData[i]->SetNumberOfValues(_num_cells);
////      for(int j=0; j<_num_cells; j++){
////          _cellCenterData[i]->SetValue(j,_varMatrix[i][j]);
////      }
////
////    }
//
//}
//
//void c_VTK::createNodalData(){
//}
//
void c_VTK::createGrid(){

    _unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    _unstructuredGrid->SetPoints(_points);
    _unstructuredGrid->SetCells(VTK_VOXEL, _cellArray);
//    for(int i=0; i<_varSize; i++){
//      _unstructuredGrid->GetCellData()->AddArray(_cellCenterData[i]);
//    }

}
//
//string c_VTK::getParallelFileName(){
//
//    string f1, f2, ff;
//
//    f1 = _fileName;
//    f2 = ".pvtu";
//   
//    ff = f1 +f2;
//    return ff;
//
//}
//
//string c_VTK::getIndividualFileName(){
//
//    string f1, f2, f3, f4, ff;
//
//    f1 = _fileName;
//    f2 = "_";
////    f3 = to_string(_mpi_rank);
//#ifdef GARNET
//    f3 = static_cast<ostringstream*>( &(ostringstream() << _mpi_rank) )->str()
//;
//#else
//    f3 = to_string(static_cast<long long>(_mpi_rank));
//#endif
//    f4 = ".vtu";
//   
//    ff = f1 + f2 + f3 + f4;
//    return ff;
//
//}
//
void c_VTK::writeFile(){

    _writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    
    _writer->SetFileName(_fileName.c_str());

#if VTK_MAJOR_VERSION <= 5
    _writer->SetInput(_unstructuredGrid);
#else
    _writer->SetInputData(_unstructuredGrid);
#endif
    _writer->Write();

}
//
//void c_VTK::parallelWriteFile(){
//  
//  if(_mpi_rank==0){
//    _pwriter = vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
//
////    const char *fileName = getParallelFileName();
//    string fileName = getParallelFileName();
//    _pwriter->SetFileName(fileName.c_str());
////    _pwriter->SetFileName("kzahad.pvtu");
//    _pwriter->SetNumberOfPieces(_mpi_size);
//#if VTK_MAJOR_VERSION <= 5
//    _pwriter->SetInput(_unstructuredGrid);
//#else
//    _pwriter->SetInputData(_unstructuredGrid);
//#endif
//    _pwriter->Write();
//  }
//
//
//}
//
void c_VTK::fileCreation(){

    createPoints();
    createCells();
//    createCellCenterData();
    createGrid();
    writeFile();
//    parallelWriteFile();

}
//
//string getSnapshotFileName_VTKXMLParticle(int step){
//
//    string f1 = "../out_";
//    string f2 = glo_casename.c_str();
//    string f3 = "/Results/GAUSS_VTK_Particle";
//    string f4 = "_";
////    string f5 = to_string(step);
//#ifdef GARNET
//    string f5 = static_cast<ostringstream*>( &(ostringstream() << step) )->str();
//    string f6 = static_cast<ostringstream*>( &(ostringstream() << MPI_PROC_ID) )->str();
//#else
//    string f5 = to_string(static_cast<long long>(step));
//    string f6 = to_string(static_cast<long long>(MPI_PROC_ID));
//#endif
//    string f7 = "_";
//    string f8 = ".vtu";
//
//    string ff = f1 + f2 + f3 + f4 + f5 + f7 + f6 + f8;
//    return ff;
//
//}
//
//string getSnapshotFileName_PVTKXMLParticle(int step){
//
//    string f1 = "../out_";
//    string f2 = glo_casename.c_str();
//    string f3 = "/Results/GAUSS_VTK_Particle";
//    string f4 = "_";
////    string f5 = to_string(step);
//#ifdef GARNET
//    string f5 = static_cast<ostringstream*>( &(ostringstream() << step) )->str();
//    string f6 = static_cast<ostringstream*>( &(ostringstream() << MPI_PROC_ID) )->str();
//#else
//    string f5 = to_string(static_cast<long long>(step));
//    string f6 = to_string(static_cast<long long>(MPI_PROC_ID));
//#endif
//    string f7 = "_";
//    string f8 = ".pvtu";
//
//    string ff = f1 + f2 + f3 + f4 + f5 + f8;
//    return ff;
//
//}

//void OutputVTKXMLParticles(c_ProcessorDomain *ProcessorDomain, int step){
//
//   string fileName = getSnapshotFileName_VTKXMLParticle(step);
//
//   vtkSmartPointer<vtkPoints> _points;
//   vtkSmartPointer<vtkVertex> *_vertex;
//   vtkSmartPointer<vtkCellArray> _cellArray;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_proc;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_type;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_velx;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_vely;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_velz;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_accx;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_accy;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_accz;
//   vtkSmartPointer<vtkDoubleArray> _cellCenterData_fork;
////   vtkSmartPointer<vtkDoubleArray> _cellCenterData;
////   vtkSmartPointer<vtkDoubleArray> _cellCenterData;
//   vtkSmartPointer<vtkUnstructuredGrid> _unstructuredGrid;
//   vtkSmartPointer<vtkXMLUnstructuredGridWriter> _writer;
//   vtkSmartPointer<vtkXMLPUnstructuredGridWriter> _pwriter;
//
//   c_Particle_Kinetic *traverser=NULL;
//
//// Count number of particles
//   int particleCounter = 0;
//   for(int i=0; i<ProcessorDomain->processorList[MPI_PROC_ID]; i++){
//         traverser = ProcessorDomain->queen[i].queenParticle;
//         while(traverser != NULL){
//           particleCounter++;
//           traverser = traverser->next;
//         }
//   }
//
//   // Create points
//   _points = vtkSmartPointer<vtkPoints>::New();
//   traverser = NULL;
//   for(int i=0; i<ProcessorDomain->processorList[MPI_PROC_ID]; i++){
//         traverser = ProcessorDomain->queen[i].queenParticle;
//         while(traverser != NULL){
//           _points->InsertNextPoint(traverser->pos[0], traverser->pos[1], traverser->pos[2]);
//           traverser = traverser->next;
//         }
//   }
//
////  Allocate Cells
//
//   // Create Cells
//   _vertex = new vtkSmartPointer<vtkVertex>[particleCounter];
//   for(int i=0; i<particleCounter; i++){
//   _vertex[i] = vtkSmartPointer<vtkVertex>::New();
//   }
//   for(int i=0; i<particleCounter; i++){
//     for(int j=0; j<1; j++){
//        _vertex[i]->GetPointIds()->SetId(j, i);
//     }
//   }
//   _cellArray = vtkSmartPointer<vtkCellArray>::New();
//   for(int i=0; i<particleCounter; i++){
//     _cellArray->InsertNextCell(_vertex[i]);
//   }
//
//   // Write DATA
//
//   string varName1 = "MPI_PROC_ID";
//   string varName2 = "speciesType";
//   string varName3 = "vel_X";
//   string varName4 = "vel_Y";
//   string varName5 = "vel_Z";
//   string varName6 = "acc_X";
//   string varName7 = "acc_Y";
//   string varName8 = "acc_Z";
//   string varName9 = "fork";
//
//   _cellCenterData_proc = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_type = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_velx = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_vely = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_velz = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_accx = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_accy = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_accz = vtkSmartPointer<vtkDoubleArray>::New();
//   _cellCenterData_fork = vtkSmartPointer<vtkDoubleArray>::New();
//
//   _cellCenterData_proc->SetName(varName1.c_str());
//   _cellCenterData_type->SetName(varName2.c_str());
//   _cellCenterData_velx->SetName(varName3.c_str());
//   _cellCenterData_vely->SetName(varName4.c_str());
//   _cellCenterData_velz->SetName(varName5.c_str());
//   _cellCenterData_accx->SetName(varName6.c_str());
//   _cellCenterData_accy->SetName(varName7.c_str());
//   _cellCenterData_accz->SetName(varName8.c_str());
//   _cellCenterData_fork->SetName(varName9.c_str());
//
//   _cellCenterData_proc->SetNumberOfComponents(1);
//   _cellCenterData_type->SetNumberOfComponents(1);
//   _cellCenterData_velx->SetNumberOfComponents(1);
//   _cellCenterData_vely->SetNumberOfComponents(1);
//   _cellCenterData_velz->SetNumberOfComponents(1);
//   _cellCenterData_accx->SetNumberOfComponents(1);
//   _cellCenterData_accy->SetNumberOfComponents(1);
//   _cellCenterData_accz->SetNumberOfComponents(1);
//   _cellCenterData_fork->SetNumberOfComponents(1);
//
//   _cellCenterData_proc->SetNumberOfValues(particleCounter);
//   _cellCenterData_type->SetNumberOfValues(particleCounter);
//   _cellCenterData_velx->SetNumberOfValues(particleCounter);
//   _cellCenterData_vely->SetNumberOfValues(particleCounter);
//   _cellCenterData_velz->SetNumberOfValues(particleCounter);
//   _cellCenterData_accx->SetNumberOfValues(particleCounter);
//   _cellCenterData_accy->SetNumberOfValues(particleCounter);
//   _cellCenterData_accz->SetNumberOfValues(particleCounter);
//   _cellCenterData_fork->SetNumberOfValues(particleCounter);
//
//   traverser = NULL;
//   int locCounter = 0;
//   for(int i=0; i<ProcessorDomain->processorList[MPI_PROC_ID]; i++){
//         traverser = ProcessorDomain->queen[i].queenParticle;
//         while(traverser != NULL){
//           _cellCenterData_proc->SetValue(locCounter, MPI_PROC_ID);
//           _cellCenterData_type->SetValue(locCounter, traverser->type);
//           _cellCenterData_velx->SetValue(locCounter, traverser->vel[0]);
//           _cellCenterData_vely->SetValue(locCounter, traverser->vel[1]);
//           _cellCenterData_velz->SetValue(locCounter, traverser->vel[2]);
//           _cellCenterData_accx->SetValue(locCounter, traverser->acc[0]);
//           _cellCenterData_accy->SetValue(locCounter, traverser->acc[1]);
//           _cellCenterData_accz->SetValue(locCounter, traverser->acc[2]);
//           _cellCenterData_fork->SetValue(locCounter, traverser->fork);
//           traverser = traverser->next;
//           locCounter++;
//         }
//   }
//
//   //Create Grid
//   _unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
//   _unstructuredGrid->SetPoints(_points);
//   _unstructuredGrid->SetCells(VTK_VERTEX, _cellArray);
////   for(int i=0; i<_varSize; i++){
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_proc);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_type);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_velx);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_vely);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_velz);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_accx);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_accy);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_accz);
//   _unstructuredGrid->GetCellData()->AddArray(_cellCenterData_fork);
////   }
//
// // Write Individual File
//   _writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
//
//   _writer->SetFileName(fileName.c_str());
//
//#if VTK_MAJOR_VERSION <= 5
//  _writer->SetInput(_unstructuredGrid);
//#else
//  _writer->SetInputData(_unstructuredGrid);
//#endif
//  _writer->Write();
//
//  if(MPI_PROC_ID==0){
//    string pfileName = getSnapshotFileName_PVTKXMLParticle(step);
//    _pwriter = vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
//
////    const char *fileName = getParallelFileName();
//    _pwriter->SetFileName(pfileName.c_str());
////    _pwriter->SetFileName("kzahad.pvtu");
//    _pwriter->SetNumberOfPieces(MPI_PROC_TOTAL_NUM);
//#if VTK_MAJOR_VERSION <= 5
//    _pwriter->SetInput(_unstructuredGrid);
//#else
//    _pwriter->SetInputData(_unstructuredGrid);
//#endif
//    _pwriter->Write();
//  }
//
//}


