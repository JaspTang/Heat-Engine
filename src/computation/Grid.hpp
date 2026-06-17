#ifndef GRID_HPP
#define GRID_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Grid {
    private:
        int numberOfVoxels;                                             //total number of voxels in simulation
        bool threeD = false;                                            //true = simulation is 3D (x,y,*z*)
        
        //Color formatting for GridPrint()
        string color = "\033[0m";                                                   
        string resetColor = "\033[0m";
        static ostream& temperatureFormat(ostream& os); //{return os << setw(8) << fixed << setprecision(3);};
        void setColor(double val);

    public:
        //-----Simulation Buffers & Variables-----//
        int xSize, ySize, zSize;

        vector<double> Temp;
        vector<double> x,y,z;

        //-----Constructor & Destructor-----//
        Grid(int xSize, int ySize, int zSize);

        ~Grid();

        //-----Printing the Grid-----//
        void GridPrint();

        //-----Getters & Setters-----//
        double getVoxelAt(int x, int y, int z);
        double getVoxelAt(int x, int y);

        void setVoxelAt(double val, int x, int y, int z);
        void setVoxelAt(double val, int x, int y);
                
        void setGrid(vector<double>& voxels);                           //set the values of the Grid to the values in a vector
};

#endif
