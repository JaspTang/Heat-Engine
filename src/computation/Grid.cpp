#include "Grid.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

// VV USED FOR TESTS VV
#include <random>

using namespace std;

class Grid {
    private:
        int numberOfVoxels;
        bool threeD = false;
        
        //PRINTING HELPER FUNCTIONS
        string color = "\033[0m";
        string resetColor = "\033[0m";
        static ostream& temperatureFormat(ostream& os) {return os << setw(8) << fixed << setprecision(3);}

        void setColor(double val) {
            if (val <= 20) {color = "\033[38;5;52m"; return;}
            if (val <= 40) {color = "\033[38;5;88m"; return;}
            if (val <= 60) {color = "\033[38;5;124m"; return;}
            if (val <= 80) {color = "\033[38;5;160m"; return;}
            if (val <= 100) {color = "\033[38;5;196m"; return;}
            if (val <= 120) {color = "\033[35m"; return;}
        }

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
            double currentTemp;

            if (threeD) {
                for (int i = 0; i < xSize; i++) {
                    cout << "z: " << i << endl;
                    for (int j = 0; j < ySize; j++) {
                        for (int k = 0; k < zSize; k++) {
                            currentTemp = Temp[k + (j * xSize) + i * (xSize * ySize)];
                            setColor(currentTemp);
                            cout << "(" << k << "," << j << "," << i << ") " 
                            << color << temperatureFormat << currentTemp << resetColor
                            << " | ";
                        }
                        cout << endl;
                    }
                }
            }
            else {
                for (int i = 0; i < xSize; i++) {
                    for (int j = 0; j < ySize; j++) {
                        currentTemp = Temp[j + i * xSize];
                        cout << "(" << j << "," << i << ") " 
                        << color << temperatureFormat << currentTemp << resetColor
                        << " | ";
                    }
                    cout << endl;
                }
            }
        }

        double getVoxelAt(int x, int y, int z) {
            //edge case 1: not 3D
            if (!threeD) throw invalid_argument("The grid is not 3D. Please try without a z coordinate.");

            //edge case 2: invalid dimensions
            if (x >= xSize || y >= ySize || z >= zSize || x < 0 || y < 0 || z < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");

            return Temp[x + (y * xSize) + z * (xSize * ySize)];
        }

        double getVoxelAt(int x, int y) {
            //edge case 1: 3D
            if (threeD) throw invalid_argument("The grid is 3D. Please try with a z coordinate.");

            //edge case 2: invalid dimensions
            if (x >= xSize || y >= ySize || x < 0 || y < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");

            return Temp[x + y * xSize];
        }

        void setVoxelAt(double val, int x, int y, int z) {
            //edge case 1: not 3D
            if (!threeD) throw invalid_argument("The grid is not 3D. Please try without a z coordinate.");

            //edge case 2: invalid dimensions
            if (x >= xSize || y >= ySize || z >= zSize || x < 0 || y < 0 || z < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");

            Temp[x + (y * xSize) + z * (xSize * ySize)] = val;
        }


        void setVoxelAt(double val, int x, int y) {
             //edge case 1: 3D
            if (threeD) throw invalid_argument("The grid is 3D. Please try with a z coordinate.");

            //edge case 2: invalid dimensions
            if (x >= xSize || y >= ySize || x < 0 || y < 0) throw invalid_argument("An invalid coordinate has been entered. Please retry.");
            
            Temp[x + y * xSize] = val;
        }


        void setGrid(vector<double>& voxels) {
            //edge case 1: mismatched dimensions
            if (voxels.size() != Temp.size()) throw invalid_argument("The given number of voxels does not match the expected number of voxels.");

            for (int i = 0; i < numberOfVoxels; i++) {
                Temp[i] = voxels[i];
            }
        }

};

//PUT THIS INTO THE TEST FILES TODO
int main() {
    int x = 10;
    int y = 10;
    int z = 10;

    Grid* simulation = new Grid(x,y,z);
    
    //Test 1: print the Grid as is
    //simulation->GridPrint();
    
    //Test 2: print the Grid with random values
    random_device rng;

    mt19937 gen(rng());

    uniform_int_distribution<> dist(1,100);

    vector<double> testSimulation(1000);

    for (int i = 0; i < 1000; i++) {
        testSimulation[i] = (double)dist(gen);
    }

    simulation->setGrid(testSimulation);

    simulation->GridPrint();

    //Test3: get and set tests
    cout << simulation->getVoxelAt(9,8,7) << endl;

    //------END OF TESTS------
    delete simulation;
    return 0; 
}
