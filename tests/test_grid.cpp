#include "Grid.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

#include <random>

using namespace std;

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
