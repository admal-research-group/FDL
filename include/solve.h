/*
 * solve.h
 *
 *  Created on: Aug 16, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_SOLVE_H_
#define INCLUDE_SOLVE_H_
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/SparseCholesky"
#include "typedef.h"

void removeRow(SpMat& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

	Eigen::SparseMatrix<double,Eigen::RowMajor> prunedRowMajor(numRows,numCols);
    if(rowToRemove > 0)
		prunedRowMajor.middleRows(0,rowToRemove)= matrix.middleRows(0,rowToRemove);
	if (rowToRemove < numRows)
		prunedRowMajor.middleRows(rowToRemove,numRows-rowToRemove)= matrix.middleRows(rowToRemove+1,numRows-rowToRemove);

    matrix.resize(numRows,numCols);
    matrix= prunedRowMajor;

}

void removeColumn(SpMat& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

	Eigen::SparseMatrix<double,Eigen::ColMajor> prunedColMajor(numRows,numCols);


	if (colToRemove>0)
		prunedColMajor.middleCols(0,colToRemove)= matrix.middleCols(0,colToRemove);
	if (colToRemove < numCols)
		prunedColMajor.middleCols(colToRemove,numCols-colToRemove)= matrix.middleCols(colToRemove+1,numCols-colToRemove);


    matrix.resize(numRows,numCols);
    matrix= prunedColMajor;
}

MatrixXd solve(const SpMat& matrix, const MatrixXd& f)
{
	MatrixXd u(matrix.rows(),1);
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;
	Eigen::SparseMatrix<double> matrixColMajor(matrix);
	solver.compute(matrixColMajor);
	if(solver.info()!=Eigen::Success) {
	  // solving failed
	  std::cout << "Failed" << std::endl;
	}
	u= solver.solve(f);
	return u;
}

void reduce(MatrixXd& matrix, const std::set<Pair>& boundary)
{
	int deleted= 0;
	for(auto ix : range<int>(0,nx))
	{
		for(auto iy : range<int>(0,ny))
		{
			Pair p= std::make_pair(ix,iy);
			auto iter= boundary.find(p);
            // if p is an interior node
			if (iter!=boundary.end())
			{
				int row= ny*ix+iy;
				int col= ny*ix+iy;
				removeRow(matrix,row-deleted);
				removeColumn(matrix,col-deleted);
				deleted++;
			}
		}
	}
}



#endif /* INCLUDE_SOLVE_H_ */
