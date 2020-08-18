#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "Eigen/Core"
#include "range.h"
#include "LDO.h"
#include "solve.h"

typedef Eigen::Matrix<double,Eigen::Dynamic, Eigen::Dynamic,Eigen::RowMajor> MatrixXd;
typedef std::pair<int,int> Pair;

int main()
{
	int nx= 20;
	int ny= 20;

	Diff<1,0,CenterDiff> dx;
	Diff<2,0,CenterDiff> dx2;
	Diff<2,2,CenterDiff> dx2dy2;
	Diff<6,0,CenterDiff> dx6;
	Diff<4,0,CenterDiff> dx4;
	Diff<4,2,CenterDiff> dx4dy2;
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

	std::cout << "Number of boundary nodes: " << boundary.size() << std::endl;

	// Assemble the reduced matrix
	MatrixXd matrix= l.assemble(nx,ny,1);

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
	force(interior.size()/2+ny/2-2)= 1;

	MatrixXd u= solve(matrix,force);

	int index= 0;
	for (const auto& elem : interior)
	{
		std::cout << elem.first  << std::setw(4)
				  << elem.second << std::setw(15)
				  << u(index) << std::endl;
		index++;
	}



	// input forcing term
	//MatrixXd u= solve(assembly,force);

    return 0;
}
