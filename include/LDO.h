/*
 * LDO.h
 *
 *  Created on: Aug 16, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_LDO_H_
#define INCLUDE_LDO_H_

#include <iostream>
#include <iomanip>
#include "Eigen/Core"
#include "Eigen/Sparse"
#include <vector>
#include "typedef.h"


struct CenterDiff
{
    static const std::map<int,double> shifts1;
    static const std::map<int,double> shifts2;

};
const std::map<int,double> CenterDiff::shifts1{{1,0.5},{0,0},{-1,-0.5}};
const std::map<int,double> CenterDiff::shifts2{{1,1.0},{0,-2.0},{-1,1.0}};

// A Linear Differential Operator class
// contains: operator () (function, point, h)
//			 	computes the value of the resulting function at a point p using the grid spacing h.
template<typename T>
class LDO
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

};


template<typename T1, typename T2>
class LDOSum : public LDO<LDOSum<T1,T2>>
{
public:
	T1 l1;
	T2 l2;
	LDOSum(const T1& l1,const T2& l2) : l1(l1),l2(l2)
    { }
	SpMat assemble(const Grid& grid) const
	{
		SpMat matrix_l1= l1.assemble(grid);
		SpMat matrix_l2= l2.assemble(grid);

		SpMat matrix= matrix_l1+ matrix_l2;
		return matrix;
	}
};

template<typename T1, typename T2>
class LDOProd: public LDO<LDOProd<T1,T2>>
{
public:
	T1 l1;
	T2 l2;
	LDOProd(const T1& l1,const T2& l2) : l1(l1),l2(l2){}
	SpMat assemble(const Grid& grid) const
	{
		SpMat matrix_l1= l1.assemble(grid);
		SpMat matrix_l2= l2.assemble(grid);
		return matrix_l1*matrix_l2;
	}

};

template<typename T>
class LDOProd<double,T>: public LDO<LDOProd<double,T>>
{
public:
	double c;
	T l;
	LDOProd(const double& c,const T& l) : c(c),l(l) { }
	SpMat assemble(const Grid& grid) const
	{
		SpMat matrix= l.assemble(grid);
		return c*matrix;
	}

};

template<typename T1,typename T2>
LDOSum<T1,T2> operator+(const LDO<T1>& l1, const LDO<T2>& l2)
{
	return LDOSum<T1,T2>(l1.derived(),l2.derived());
}

template<typename T1, typename T2>
LDOProd<T1,T2> operator*(const LDO<T1>& l1, const LDO<T2>& l2)
{
	return LDOProd<T1,T2>(l1.derived(),l2.derived());
}
template<typename T>
LDOProd<double,T> operator*(const double& c, const LDO<T>& l)
{
	return LDOProd<double,T>(c,l.derived());
}

template<int NX,int NY, typename T>
class Diff : public LDO<Diff<NX,NY,T>>
{
public:
	Stencil stencil;

	Diff()
	{
		Stencil begin,temp;

		// begin with the identity stencil
		begin.emplace(std::make_pair(0,0),1);

		int nx= NX;
		int ny= NY;
		while(nx>0 || ny>0)
		{
			temp.clear();
			std::map<int,double> shifts;
			if (ny>1 || (nx>1 && ny==0))
				shifts= T::shifts2;
			else
				shifts= T::shifts1;

			for(const auto& elem : begin)
			{
				for(const auto s : shifts)
				{
					// shift the grid point in elem
					std::pair<int,int> ij(ny>0 ?
							std::make_pair(elem.first.first,elem.first.second+s.first) :
							std::make_pair(elem.first.first+s.first,elem.first.second));

					// find the shifted grid point in stencil
					auto iter(temp.find(ij));
					if(iter==temp.end())
					{
						temp.emplace(ij,elem.second*s.second);
					}
					else
					{
						iter->second+=elem.second*s.second;
					}
				}
			}
			begin= temp;

			if (ny>1) ny= ny-2;
			else if (ny==1) ny= ny-1;
			else if (nx>1) nx= nx-2;
			else nx= nx-1;
		}

		stencil= temp;
	}


	void displayStencil()
	{
		for (const auto& elem : stencil)
			std::cout << elem.first.first << std::setw(8) << elem.first.second << std::setw(8) << elem.second << std::endl;
	}
	void displayStencil() const
	{
		for (const auto& elem : stencil)
			std::cout << elem.first.first << std::setw(8) << elem.first.second << std::setw(8) << elem.second << std::endl;
	}


	SpMat assemble(const Grid& grid)
	{
		SpMat mat(grid.nx*grid.ny,grid.nx*grid.ny);
		std::vector<Triplet> coefficients;
		int index= 0;
		for (int i_nx=0; i_nx<grid.nx; i_nx++)
		{
			for (int i_ny=0; i_ny<grid.ny; i_ny++)
			{
				for (const auto& elem : stencil)
				{
					auto elemIndex= std::make_pair(i_nx+elem.first.first, i_ny+elem.first.second);

					if (elemIndex.first<grid.nx && elemIndex.second<grid.ny &&
						elemIndex.first>=0 && elemIndex.second>=0)
					{
						Triplet t= Triplet(i_nx*grid.ny+i_ny,
										   elemIndex.first*grid.ny+elemIndex.second,
										   elem.second/pow(h,NX+NY));
						coefficients.push_back(t);
						//mat(i_nx*ny+i_ny,elemIndex.first*ny+elemIndex.second)= elem.second/pow(h,NX+NY);
					}
				}
				index= index+1;
			}
		}
		mat.setFromTriplets(coefficients.begin(), coefficients.end());
		return mat;
	}

	SpMat assemble(const Grid& grid) const
	{
		SpMat mat(grid.nx*grid.ny,grid.nx*grid.ny);
		std::vector<Triplet> coefficients;
		int index= 0;
		for (int i_nx=0; i_nx<grid.nx; i_nx++)
		{
			for (int i_ny=0; i_ny<grid.ny; i_ny++)
			{
				for (const auto& elem : stencil)
				{
					auto elemIndex= std::make_pair(i_nx+elem.first.first, i_ny+elem.first.second);

					if (elemIndex.first<grid.nx && elemIndex.second<grid.ny &&
						elemIndex.first>=0 && elemIndex.second>=0)
					{
						Triplet t= Triplet(i_nx*grid.ny+i_ny,
										   elemIndex.first*grid.ny+elemIndex.second,
										   elem.second/pow(h,NX+NY));
						coefficients.push_back(t);
						//mat(i_nx*ny+i_ny,elemIndex.first*ny+elemIndex.second)= elem.second/pow(h,NX+NY);
					}
				}
				index= index+1;
			}
		}
		mat.setFromTriplets(coefficients.begin(), coefficients.end());
		return mat;
	}
};





#endif /* INCLUDE_LDO_H_ */
