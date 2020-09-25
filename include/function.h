/*
 * function.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_FUNCTION_H_
#define INCLUDE_FUNCTION_H_

#include "typedef.h"
#include "grid.h"

template<typename T>
class Function
{
public:
	T& derived()
	{
		return *static_cast<T*>(this);
		//return static_cast<T&>(*this);
	}
	const T& derived() const
	{
		return *static_cast<const T*>(this);
		//return static_cast<const T&>(*this);
	}

	double operator()(const Paird& p)
	{
		return *static_cast<T*>(this)(p);
	}
	double operator()(const Paird& p) const
	{
		return *static_cast<T*>(this)(p);
	}
};

class GridFunction : public Function<GridFunction>
{
public:
	Grid grid;
	VectorXd function;

	GridFunction(const Grid& grid, const VectorXd& function) : grid(grid),function(function)
	{
		assert(function.cols()==grid.nx * grid.ny);
	}
	GridFunction(const Grid& grid) : grid(grid)
	{
		function= VectorXd::Zero(grid.nx*grid.ny);
	}

	double operator()(const Paird& p)
	{
		double result= 0;
		int pxmin= p.first/grid.h;
		int pymin= p.second/grid.h;

		int index= pxmin*grid.ny+pymin;
		result= function(index);
		index= pxmin*grid.ny+pymin+1;
		result= result+function(index);
		index= (pxmin+1)*grid.ny+pymin;
		result= result+function(index);
		index= (pxmin+1)*grid.ny+pymin+1;
		result= result+function(index);
		return result;
	}
	double operator()(const Paird& p) const
	{
		double result= 0;
		int pxmin= p.first/grid.h;
		int pymin= p.second/grid.h;

		int index= pxmin*grid.ny+pymin;
		result= function(index);
		index= pxmin*grid.ny+pymin+1;
		result= result+function(index);
		index= (pxmin+1)*grid.ny+pymin;
		result= result+function(index);
		index= (pxmin+1)*grid.ny+pymin+1;
		result= result+function(index);
		return result;
	}
};



#endif /* INCLUDE_FUNCTION_H_ */
