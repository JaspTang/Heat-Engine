#include "Grid.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class Grid {
    private:
        int numberOfVoxels;
        bool threeD = false;

    public:
        int xSize;
        int ySize;
        int zSize;

        vector<double> Temp;
        vector<double> x, y, z;

        Grid(int xSize, int ySize, int zSize) {
            this->xSize = xSize;
            this->ySize = ySize;
            this->zSize = zSize;
                                         
            //Dimension Error bounds #1
            if (xSize <= 0 || ySize <= 0) {
                throw invalid_argument(
                    "X and Y dimensions cannot be 0 or negative."
                );
            }

            //Dimension Error bounds #2
            if (zSize > 0) threeD = true;
            
            //Calculate total number of Voxels
            if (threeD) numberOfVoxels = xSize * ySize * zSize;
            else numberOfVoxels = xSize * ySize;
            
            //initialize buffers
            Temp.resize(numberOfVoxels);
            fill(Temp.begin(), Temp.end(), 0.0);
            
            //done; let user know
            if (threeD) cout << "Grid with " << numberOfVoxels << " Voxels created. [" << xSize << " x " << ySize << " x " << zSize << "]" << endl; 
            else  cout << "Grid with " << numberOfVoxels << " Voxels created. [" << xSize << " x " << ySize << "]" << endl; 
        }

        ~Grid() {
            //TODO
            xSize = 0;
            ySize = 0;
            zSize = 0;
            numberOfVoxels = 0;
        }
        
        //print the GridOutput as it currently is (x,y,z) Temperature
        void GridPrint() {
            if (threeD) {
                for (int i = 0; i < xSize; i++) {
                    cout << "z: " << i << endl;
                    for (int j = 0; j < ySize; j++) {
                        for (int k = 0; k < zSize; k++) {
                            cout << "(" << k << "," << j << "," << i << ") " << Temp[i+j+k] << " | "; //figure out indexing system TODO
                        }
                        cout << endl;
                    }
                }
            }
            else {
                for (int i = 0; i < xSize; i++) {
                    for (int j = 0; j < ySize; j++) {
                        cout << "(" << j << "," << i << ") " << Temp[i+j] << " | ";
                    }
                    cout << endl;
                }
            }
        }

        double getVoxelAt(int x, int y, int z) {
            //edge case 1: not 3D
            if (!threeD) throw invalid_argument("The grid is not 3D. Please try without a z coordinate.");

            //edge case 2: ivalid dimensions
            if (x >= xSize || y >= ySize || z >= zSize || x < 0 || y < 0 || z < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");

            return Temp[x + y * xSize + z * (xSize * ySize)];
        }

        double getVoxelAt(int x, int y) {
            //edge case 1: 3D
            if (threeD) throw invalid_argument("The grid is 3D. Please try with a z coordinate.");

            //edge case 2: invalid dimensions
            if (x >= xSize || y >= ySize || x < 0 || y < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");

            return Temp[x + y * xSize];
        }

        void setGrid(//TODO) {

        }
};

int main() {
    int x = 10;
    int y = 10;
    int z = 10;

    Grid* simulation = new Grid(x,y,z);

    simulation->GridPrint();

    delete simulation;
    return 0; 
}
