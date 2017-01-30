#include "output.h"

using namespace std;

void rtbtDumpUnstructuredMesh(string fileName, int numNodes, int numNodesPerCell, int numCells, double *x, double *y, double *z, int **cellCon, string fileType){

    c_Output *Output = NULL;
    Output = new c_Output();
    
    Output->setFileName(fileName);
    Output->setMeshParameters(numNodes, numNodesPerCell, numCells);
    Output->setNodeXYZPositions(x,y,z);
    Output->setCellConnectivity(cellCon);
    Output->setFileType(fileType);
    Output->createCorrespondingFile();

}

//void OutputResults(c_ProcessorDomain *ProcessorDomain, int step, 
//         int OutputCells, c_Mesh_Kinetic_Output<c_Cell_AMR_Kinetic> *oMesh, 
//         int CollisionCells, c_Mesh_Kinetic_Output<c_Cell_AMR_Kinetic> *cMesh, 
//         int PICCells, c_Mesh_Kinetic_Output<c_Cell_AMR_Kinetic> *pMesh, 
//         int numberOfSamples){
//
//   int type_flag = 1; // for output mesh(sampling)
//   outputAMRVTK(type_flag, ProcessorDomain, step, OutputCells, oMesh, numberOfSamples);
//
//}
   // Reduce all Panel related Values using MPI

//void outputAMRVTK(int type_flag, c_ProcessorDomain *ProcessorDomain, int step, int NumberOfCellsPassedFromSolver, c_Mesh_Kinetic_Output<c_Cell_AMR_Kinetic> *Mesh, int numberOfSamples){
//
//   string fileName;
//   if(type_flag == 1){
//     fileName = getSnapshotFileName_Output(step);
//   }
//   else if(type_flag == 2){
//     fileName = getSnapshotFileName_Collision(step);
//   }
//   else if(type_flag == 3){
//     fileName = getSnapshotFileName_PIC(step);
//   }
//
//   char *gridName = "Unstructered" ;
//   char *gridType = "Uniform" ;
//   char *topoType = "Hexahedron" ;
//   int cellNum = NumberOfCellsPassedFromSolver;
//   int nodePerCell = 8;//Hexahedron
//   int nodeNum = nodePerCell * cellNum;
//   int numberOfVarName = 11+8*glo_NumberOfSpecies + 1; // include MPI_PROCID
////   int varSize = ;
//
//   c_GridStoringAMR *AMR = new c_GridStoringAMR(NumberOfCellsPassedFromSolver, Mesh, numberOfSamples, numberOfVarName);
//    
////   AMR->setVariables(NumberOfCellsPassedFromSolver, Mesh, numberOfSamples, varSize);
//   AMR->setNodes();
//   AMR->setValues();
//
//   int **cells=NULL;
//   cells = new int *[cellNum];
//   for(int i =0; i<cellNum; i++){
//     cells[i] = new int [nodePerCell];
//   }
//
//   for(int i=0;i<cellNum;i++){
//     for(int j=0;j<nodePerCell;j++){
//       cells[i][j]=AMR->cellCon[8*i+j];
//     }
//   }
//
//   string *vtkVarName;
//   vtkVarName = new string[numberOfVarName];
//
//   // look in geometry/def_cell.cpp for the definition of the variaable list
//   vtkVarName[0] = "dx [m]";
//   vtkVarName[1] = "cellVol [m3]";
//   vtkVarName[2] = "debye [m]";
//   vtkVarName[3] = "MFP [m]";
//   vtkVarName[4] = "Potential [V]";
//   vtkVarName[5] = "E(x) [V/m]";
//   vtkVarName[6] = "E(y) [V/m]";
//   vtkVarName[7] = "E(z) [V/m]";
//   vtkVarName[8] = "B(x) [T]";
//   vtkVarName[9] = "B(y) [T]";
//   vtkVarName[10] = "B(z) [T]";
//
//   string ext_n = " n [#/m3]";
//   string ext_u = " U(x) [m/s]";
//   string ext_v = " U(y) [m/s]";
//   string ext_w = " U(z) [m/s]";
//   string ext_Ttr = " Ttr [K]";
//   string ext_Trot = " Trot [K]";
//   string ext_Tvib = " Tvib [K]";
//   string ext_Telec = " Telec [K]";
//
//   int specIndex=0;
//   for(int ispec=0;ispec<glo_NumberOfSpecies;ispec++){
//     specIndex = 11 + 8*ispec;
//     vtkVarName[specIndex] = glo_chemList[ispec] + ext_n;
//     vtkVarName[specIndex+1] = glo_chemList[ispec] + ext_u;
//     vtkVarName[specIndex+2] = glo_chemList[ispec] + ext_v;
//     vtkVarName[specIndex+3] = glo_chemList[ispec] + ext_w;
//     vtkVarName[specIndex+4] = glo_chemList[ispec] + ext_Ttr;
//     vtkVarName[specIndex+5] = glo_chemList[ispec] + ext_Trot;
//     vtkVarName[specIndex+6] = glo_chemList[ispec] + ext_Tvib;
//     vtkVarName[specIndex+7] = glo_chemList[ispec] + ext_Telec;
//   }
//   vtkVarName[specIndex+8] = "MPI_PROC_ID";
//  
//   vector<string> vtkStringVec;
////   vtkStringVec.begin();   
//   for(int ivtk=0;ivtk<numberOfVarName;ivtk++){
//     vtkStringVec.push_back(vtkVarName[ivtk]);
//   }
//
//   /*define cell distribution among processors.*/
//   MPI_Info info  = MPI_INFO_NULL;
//
//   liberOutVector(fileName, gridName, gridType, topoType, cellNum, nodePerCell, nodeNum, numberOfVarName, vtkStringVec, AMR->cellData, AMR->x, AMR->y, AMR->z,cells,
//   info, comm);
//
//// delete allocated arrays
//
//   for (int i=0;i<cellNum;i++){
//     delete [] cells[i];
//     cells[i]=NULL;
//   }
//   delete [] cells;
//   cells=NULL;
// 
//   delete AMR;
//   AMR = NULL;
//
//   if(MPI_PROC_ID==0){
//     if(type_flag == 1){
//       cout << "VTK files are outputted for output mesh." << '\n';
//     }
//     else if(type_flag == 2){
//       cout << "VTK files are outputted for collision mesh." << '\n';
//     }
//     else if(type_flag == 3){
//       cout << "VTK files are outputted for pic mesh." << '\n';
//     }
//   }
//
//}


/*
void outputAMRTecplot(c_ProcessorDomain *ProcessorDomain, int step, int NumberOfCellsPassedFromSolver, c_Mesh_Kinetic_Output<c_Cell_AMR_Kinetic> *Mesh, int numberOfSamples){

   string fileName = getSnapshotFileName_OutputTecplot(step);
   char *gridName = "Unstructered" ;
   char *gridType = "Uniform" ;
   char *topoType = "Hexahedron" ;
   int cellNum = NumberOfCellsPassedFromSolver;
   int nodePerCell = 8;//Hexahedron
   int nodeNum = nodePerCell * cellNum;
   int varSize = 28;

   ofstream outmyfile;
   outmyfile.open(fileName.c_str());
   
   if(MPI_PROC_ID == 0){
     outmyfile << "title = \"GAUSS TECPLOT\"" << '\n';
     outmyfile << "variables = \"x(m)\", \"y(m)\", \"z(m)\", \"n1(#/m3)\", \"u1(m/s)\", \"v1(m/s)\", \"w1(m/s)\", \"T1(m/s)\", \"n2(#/m3)\", \"u2(m/s)\", \"v2(m/s)\", \"w2(m/s)\", \"T2(m/s)\", \"Potential\", \"E_x\", \"E_y\", \"E_z\", \"MFPRatio\", \"Debye\", \"dx\", \"nb1(#/m3)\", \"ub1(m/s)\", \"vb1(m/s)\", \"wb1(m/s)\", \"Tb1(m/s)\", \"n2c(#/m3)\", \"u2c(m/s)\", \"v2c(m/s)\", \"w2c(m/s)\", \"T2c(m/s)\", \"ProcID\"" << '\n';
   }
   outmyfile << " zone T = \"sug_" << MPI_PROC_ID << "\", n=" << 8*NumberOfCellsPassedFromSolver << " ,e=" << NumberOfCellsPassedFromSolver << " ,DATAPACKING=BLOCK, ZONETYPE=FEBRICK" << '\n';
   outmyfile << " VARLOCATION = ([4-31] = CELLCENTERED)" << '\n';

   c_GridStoringAMR *AMR = new c_GridStoringAMR(NumberOfCellsPassedFromSolver, Mesh, numberOfSamples, varSize);
    
   AMR->setNodes();
   AMR->setValues();

   int **cells=NULL;
   cells = new int *[cellNum];
   for(int i =0; i<cellNum; i++){
     cells[i] = new int [nodePerCell];
   }

   for(int i=0;i<cellNum;i++){
     for(int j=0;j<nodePerCell;j++){
       cells[i][j]=AMR->cellCon[8*i+j];
     }
   }
   
   outmyfile << '\n';
   for(int i =0; i<nodeNum; i++){
     outmyfile << AMR->x[i] << " ";
     if((i%1000 == 0) && (i != 0)){
       outmyfile << '\n';
     } 
   }
   outmyfile << '\n';
   for(int i =0; i<nodeNum; i++){
     outmyfile << AMR->y[i] << " ";
     if((i%1000 == 0) && (i != 0)){
       outmyfile << '\n';
     } 
   }
   outmyfile << '\n';
   for(int i =0; i<nodeNum; i++){
     outmyfile << AMR->z[i] << " ";
     if((i%1000 == 0) && (i != 0)){
       outmyfile << '\n';
     } 
   }
   outmyfile << '\n';
   for(int i =0; i<varSize; i++){
     for(int j =0; j<cellNum; j++){
       outmyfile << AMR->cellData[i][j] << " ";
       if((j%1000 == 0) && (j != 0)){
       outmyfile << '\n';
       }
     }
     outmyfile << '\n';
   }
   outmyfile << '\n';
   for(int i =0; i<cellNum; i++){
//     for(int j =0; j<8; j++){
//       outmyfile << cells[i][j]+1 << " ";
//     }
     outmyfile << cells[i][0]+1 << " ";
     outmyfile << cells[i][1]+1 << " ";
     outmyfile << cells[i][3]+1 << " ";
     outmyfile << cells[i][2]+1 << " ";
     outmyfile << cells[i][4]+1 << " ";
     outmyfile << cells[i][5]+1 << " ";
     outmyfile << cells[i][7]+1 << " ";
     outmyfile << cells[i][6]+1 << " ";
     outmyfile << '\n';

   }

//delete allocated arrays

  for (int i=0;i<cellNum;i++){
    delete [] cells[i];
    cells[i]=NULL;
  }
  delete [] cells;
  cells=NULL;

  delete AMR;
  AMR = NULL;

  if(MPI_PROC_ID==0){
    cout << "Tecplot files are outputted for output mesh." << '\n';
  }

}

*/
