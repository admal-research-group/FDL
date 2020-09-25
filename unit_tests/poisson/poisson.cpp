#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>
#include "Eigen/Core"
#include "range.h"
#include "LDO.h"
#include "solve.h"
#include "Eigen/Sparse"
#include "typedef.h"
#include "grid.h"
#include "function.h"



int main()
{
	Grid grid(40,40,1.0/40);

	Diff<2,0,CenterDiff> dx2;
	Diff<0,2,CenterDiff> dy2;
	auto l= dx2+dy2;

	// specify boundary nodes
	int nlayersx= 1;
	int nlayersy= 1;
	std::set<Pair> boundary= grid.boundaryNodes(nlayersx,nlayersy);

    // specify initial conditions
	GridFunction u(grid);

    // specify boundary conditions

	// Assemble the reduced matrix
    SpMat matrix= l.assemble(grid);

    MatrixXd matrixInterior= reduce(matrix,boundary);
    MatrixXd uInterior= reduce(u.function,boundary);
	GridFunction force(grid);
	force.function(grid.nx*grid.ny/2+grid.ny/2,0)= 1;


    // MatrixXd u= expand(uInterior,boundary);

	// Solve
    // u(t+dt)= u(dt) + dt* (L u(dt)+f)
	//MatrixXd u= solve(matrix,force);

    MatrixXd uNext= MatrixXd::Zero(interior.size(),1);
    double dt= 0.0001;

    // explicit evolution
    std::string file= "u.txt";
    std::ofstream write_file(file);
    for(const auto& i : range<int>(0,1000))
    {
        //write_file << "Time: " << i*dt << std::endl;
        // write the solution to u.txt
        int index= 0;
        for (const auto& elem : interior)
        {
            write_file << elem.first  << std::setw(8)
                       << elem.second << std::setw(25)
                       << std::setprecision(15) << uNext(index) << std::endl;
            index++;
        }
        uNext= u + dt*(matrix*u+force);
        u= uNext;
    }

    return 0;
}
