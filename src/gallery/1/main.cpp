#include <iostream>
#include <fstream>
#include <string>

#include "pavlov.h"

using namespace std;

int main(){

   double minPos[3] = {0.0, 0.0, 0.0};
   double maxPos[3] = {4.0, 2.0, 1.0};
   int numGridPoints[3] = {33, 17, 9};

   // Create node positions
   double *x, *y, *z;

   x = NULL;
   y = NULL;
   z = NULL;

   int numPoints = numGridPoints[0] * numGridPoints[1] * numGridPoints[2];
   
   x = new double[numPoints];
   y = new double[numPoints];
   z = new double[numPoints];

   double deltaX = (maxPos[0] - minPos[0]) / (numGridPoints[0] -1);
   double deltaY = (maxPos[1] - minPos[1]) / (numGridPoints[1] -1);
   double deltaZ = (maxPos[2] - minPos[2]) / (numGridPoints[2] -1);

   int point_index = 0;
   for(int ix=0;ix<numGridPoints[0];ix++){
     for(int iy=0;iy<numGridPoints[1];iy++){
       for(int iz=0;iz<numGridPoints[2];iz++){
         point_index = (numGridPoints[1]*numGridPoints[2]) * ix + numGridPoints[2] * iy + iz;
         x[point_index] = minPos[0] + deltaX * double(ix);
         y[point_index] = minPos[1] + deltaY * double(iy);
         z[point_index] = minPos[2] + deltaZ * double(iz);
       }
     }
   }
  
   for(int ix=0;ix<numGridPoints[0];ix++){
     for(int iy=0;iy<numGridPoints[1];iy++){
       for(int iz=0;iz<numGridPoints[2];iz++){
         point_index = (numGridPoints[1]*numGridPoints[2]) * ix + numGridPoints[2] * iy + iz;
//         cout << "design " << x[point_index] << " " << y[point_index] << " " << z[point_index] << '\n';
       }
     }
   }

   // cell connectivity
   
   int numPointsPerCell = 8;
   int numCells = (numGridPoints[0]-1) * (numGridPoints[1]-1) * (numGridPoints[2] -1);
   
   int **cellCon = NULL;
   cellCon = new int *[numCells];
   for(int icell=0;icell<numCells;icell++){
     cellCon[icell] = NULL;
     cellCon[icell] = new int[numPointsPerCell];
   }
   
   int cell_index = 0;
   for(int ix=0;ix<(numGridPoints[0]-1);ix++){
     for(int iy=0;iy<(numGridPoints[1]-1);iy++){
       for(int iz=0;iz<(numGridPoints[2]-1);iz++){
         point_index = numGridPoints[1]*numGridPoints[2] * ix + numGridPoints[2]* iy + iz;
         cell_index = ((numGridPoints[1]-1)*(numGridPoints[2]-1)) * ix + (numGridPoints[2]-1) * iy + iz;
         cellCon[cell_index][0] = point_index;  
         cellCon[cell_index][1] = numGridPoints[1]*numGridPoints[2] + point_index;  
         cellCon[cell_index][2] = point_index + numGridPoints[2];  
         cellCon[cell_index][3] = numGridPoints[1]*numGridPoints[2] + point_index + numGridPoints[2];  
         cellCon[cell_index][4] = point_index + 1;  
         cellCon[cell_index][5] = numGridPoints[1]*numGridPoints[2] + point_index + 1;  
         cellCon[cell_index][6] = point_index + numGridPoints[2] + 1;  
         cellCon[cell_index][7] = numGridPoints[1]*numGridPoints[2]+ point_index + numGridPoints[2] + 1;  

       }
     }
   }

   // Dump manual VTK file
//   string fileName_manual = "manual_file.vtk";
//
//   ofstream outmyfile;
//
//   outmyfile.open(fileName_manual.c_str());
//   outmyfile << "# vtk DataFile Version 2.0" << '\n';
//   outmyfile << "Pavlov example" << '\n';
//   outmyfile << "ASCII" << '\n';
//   outmyfile << "DATASET UNSTRUCTURED_GRID" << '\n';
//   outmyfile << "POINTS " << numPoints << " float"<< '\n';
// 
//   for(int ix=0;ix<numGridPoints[0];ix++){
//     for(int iy=0;iy<numGridPoints[1];iy++){
//       for(int iz=0;iz<numGridPoints[2];iz++){
//         point_index = (numGridPoints[1]*numGridPoints[2]) * ix + numGridPoints[2] * iy + iz;
//         outmyfile << x[point_index] << " " << y[point_index] << " " << z[point_index] << '\n';
//       }
//     }
//   }
//
//   outmyfile << "CELLS " << numCells << " " << 9*numCells << '\n';
//
//   for(int i=0; i<numCells; i=i++){
//     outmyfile << "8 ";
//     for(int j=0; j<8; j=j++){
//        outmyfile << cellCon[i][j] << " ";
//     }
//     outmyfile << '\n';
//   }
//
//   outmyfile << "CELL_TYPES " << numCells << '\n';
//
//   for(int i=0; i<numCells; i=i++){
//     outmyfile << "11" << '\n';
//   }

   // Call Pavlov library

   string fileName = "pavlov.vtu";
   string fileType = "VTK";
   
   pavlov_createUnstructuredMesh(fileName, numPoints, numPointsPerCell, numCells, x, y, z, cellCon, fileType);    

   cout << "Tester function has finished." << '\n';

}
