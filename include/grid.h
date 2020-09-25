/*
 * grid.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_GRID_H_
#define INCLUDE_GRID_H_

class Grid
{
public:
	int nx;
	int ny;
	double h;

	Grid(const int& nx, const int& ny, const double& h) : nx(nx),ny(ny),h(h){}

	std::set<Pair> boundaryNodes(const int& nlayersx, const int& nlayersy)
	{
		std::set<Pair> boundary;
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
		return boundary;
	}
};






#endif /* INCLUDE_GRID_H_ */
