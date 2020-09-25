#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>
#include "Eigen/Core"
#include "LDO.h"
#include "Eigen/Sparse"
#include "typedef.h"

int main()
{
	int nx= 40;
	int ny= 40;

	Diff<2,0,CenterDiff> dx2;
	Diff<0,2,CenterDiff> dy2;
	//auto l= (dx2+dy2)*(dx2+dy2);
	auto l= dx2*dy2*dx2;

	// Assemble the reduced matrix
	SpMat matrix= l.assemble(nx,ny,1);

    return 0;
}
