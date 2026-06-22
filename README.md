-------------------------------------------------------------------------------***HEAT ENGINE***-------------------------------------------------------------------------------------

**BIG IDEA: *I want to invent a visualization system that serves a physical simulation.***

Heat transfer in an object is an incredibly complex system that involves a lot of math.
The idea came to me as I learned the basic Heat Equation in my differential equations class. 
By solving a PDE, you were able to solve for the temperature at a given space and time, with given boundary/initial conditions (u(x,t)).

What if we treated an object like a collection of a numch of individual points, each with their own space (coordinate) and same time?
Well, we could use this heat equation to solve for a formula that would be able to describe each individual point within an object,
and thus **we could simulate heat transfer within an object.** 

However, solving a heat equation is a lot easier done by hand than in code. So, how could we make this easier?


*Ideation*
Instead of solving the heat equation every time we update the simulation - which could be technologically complex and confusing - we can simulate particles and their temperatures
as dependent upon the **interactions of neighboring particles**


*Timeline*
| Ideation
| System Design
| Learning, Developing, and Demo'ing
|  - Visualization System Work
|  - Computation Implementation
| Revisions
| Expansion, expansion, expansion
V 

*Vocab* (for clarity)
particle = individual point/voxel in our simulation
 - for every particle, we are performing the computations
 - voxel: a hypothetically small cube with volume that has a spatial density, material identity, and a temperature (and implicitly described by a location within an object/space)

*System Design*
An important distinction must be made between visualization and computation. 
Because I want the simulation to be as low-level as possible, we must aknowledge that a GPU both has computation and "visualization" purposes.
Therefore, the system (and project) will be divided/abstracted into two parts: **Computation** and **Visualization**

                Computation                                                     Visualization
            -Compute the interactions                                       -Display voxels as individual
            between neighbors                                               points/particles
            /               \                                               /                   \
           /                 \                                             /                     \
         Lang.              Math                                        Lang./Tools             Math/Concepts
         Cuda               Neighbor Int.                               C++                     Scientific Field Visualization
         C                  Voxel Repres.                               SDL                     Voxel Rendering
         ARM                Buffer Int.                                 OpenGL                  Grid-based Coordinates


*Voxel Representation Differences between Computation aand Visualization Layers*
Computation: Voxel is volume, density, temperature, material
Visualization: Voxel is point, temperature

*Why am I making a specific visualization aspect? Why not use what's out there already?*
I really want to learn/increase my knowledge on how GPUs work/compute - in general, **how to harness the power into GPUs to achieve mindblowing results**
Going back to my "Big Idea", I want to invent a specific visualization system that serves my original purpose of building a heat simulation.
This will give me experience and a deeper, fulfilling idea of:
 - GPU interfacing
 - Graphical API's
 - Cuda Implementation & Use
 - Graphics Drivers
 - Graphics Engines

*Project Design*
**Heat Engine**
│
├── src/
│    ├── computation/
│    │      ├── Grid.hpp
│    │      ├── Grid.cpp
│    │      ├── HeatCompute.hpp
│    │      └── HeatCompute.cpp
│    ├── visualization/
│    │      ├── Renderer.hpp
│    │      └── Renderer.cpp
│    └── app/ 
│           └── main.cpp
├── build/
├── tests/

*Code Design*
Let's say we have a 500x500x500 theoretical space. Each unit is 1 voxel - 1 hypothetical cube of volume, material density, material type etc.
 - This would be 125 million voxels
But because we are going to be workign with lots of data and directly with the GPU, we want to enable efficient caching and operations, so we'll
use individual buffers to represent individual fields i.e. temp[12000], x[12000], etc.
 - a "vecotrized approximation of PDE fields"

Pipeline:
[Simulation Buffers]
    T, ρ, k
        ↓
[Compute step]
    update T
        ↓
[Renderer]
    reads T[i]
    maps → color
    draws point at voxel center

*Compiling & Testing*
run **make** to make the full-fledged simulation
run **make test_grid** to make the test_grid simulation
run **make run_test_grid** to run the test_grid simulation

*Visualization*
For my simulation, I will have 2 layers - a simulation time mode and a renderer time mode
The visual engine will eventually have many options to display the change in heat, including (and standard) particles, contours, irradiated heat


