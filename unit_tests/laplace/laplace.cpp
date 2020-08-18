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

int main()
{
	int nx= 20;
	int ny= 20;

	Diff<2,0,CenterDiff> dx2;
	Diff<0,2,CenterDiff> dy2;
	auto l= -1*(dx2+dy2);

	// specify boundary nodes
	std::set<Pair> boundary;
	int nlayersx= 1;
	int nlayersy= 1;
	for(auto ix : range<int>(0,nx))
	{
		for(auto n : range<int>(0,nlayersy))
		{
			boundary.insert(std::make_pair(ix,n));
			boundary.insert(std::make_pair(ix,ny-n-1));
		}
	}
	for(auto iy : range<int>(0,ny))
	{
		for(auto n : range<int>(0,nlayersx))
		{
			boundary.insert(std::make_pair(n,iy));
			boundary.insert(std::make_pair(nx-n-1,iy));
		}
	}

	// Assemble the reduced matrix
	SpMat matrix= l.assemble(nx,ny,1);
	std::vector<Pair> interior;
	int deleted= 0;
	for(auto ix : range<int>(0,nx))
	{
		for(auto iy : range<int>(0,ny))
		{
			Pair p= std::make_pair(ix,iy);
			auto iter= boundary.find(p);
			if (iter==boundary.end())
				interior.push_back(p);
			else
			{
				int row= ny*ix+iy;
				int col= ny*ix+iy;
				removeRow(matrix,row-deleted);
				removeColumn(matrix,col-deleted);
				deleted++;
			}
		}
	}

	// force
	MatrixXd force= MatrixXd::Zero(interior.size(),1);
	force(interior.size()/2+ny/2-2,0)= 1;


	// Solve
	//Eigen::Matrix<double,Eigen::Dynamic, 1,Eigen::ColMajor> u;
	MatrixXd u= solve(matrix,force);

	// write the solution to u.txt
	std::string file= "u.txt";
	std::ofstream write_file(file);
	int index= 0;
	for (const auto& elem : interior)
	{
		write_file << elem.first  << std::setw(8)
				   << elem.second << std::setw(25)
				   << std::setprecision(15) << u(index) << std::endl;
		index++;
	}

	// compare the solution to uRef.txt
	Pair gridIndex;
	double uref(0);
	index= 0;
	std::string fileReference= "uRef.txt";
	std::ifstream read_file(fileReference);
	for (const auto& elem : interior)
	{
		read_file >> gridIndex.first >> gridIndex.second >> uref;
		if (elem != gridIndex || abs(uref-u(index))>epsilon)
		{
			std::string errorMessage= "Test failed in " + fileReference +
									  ". Error in line: " + std::to_string(index)+
									  ". " + std::to_string(uref) + "   " + std::to_string(u(index));
			MY_ERROR(errorMessage);
		}
		index++;

	}

    return 0;
}
