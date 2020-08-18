/*
 * typedef.h
 *
 *  Created on: Nov 6, 2019
 *      Author: Nikhil
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

#include <iomanip>
#include <string>
#include <iostream>
#include "Eigen/Dense"
#include <memory>
#include <map>
#include <set>

#define MY_ERROR(message)                                                \
  {                                                                      \
    std::cout << "* Error : \"" << message << "\" : " << __LINE__ << ":" \
              << __FILE__ << std::endl;                                  \
    exit(1);                                                             \
  }

#define MY_WARNING(message)                                                \
  {                                                                        \
    std::cout << "* Warning : \"" << message << "\" : " << __LINE__ << ":" \
              << __FILE__ << std::endl;                                    \
  }

#define MY_BANNER(announcement)                                            \
  {                                                                        \
	std::cout << "--------------------------------------------------------------------------------" << "\n";\
	std::cout << std::setw(40+strlen(announcement)/2)<< announcement << "\n";\
	std::cout << "--------------------------------------------------------------------------------" << "\n";\
  }
#define MY_HEADING(heading)                                             \
{																		\
	std::cout << "\n";													\
	std::cout << heading << "\n";										\
	std::cout << std::string(strlen(heading),'-')<< "\n";				\
}
#define MY_LINE(message)                                             	\
{																		\
	std::cout << message << "\n";										\
}
#define MY_SUBLINE(message)                                             \
{																		\
	std::cout << "     " << message << "\n";							\
}


typedef Eigen::Matrix<double,Eigen::Dynamic, Eigen::Dynamic,Eigen::RowMajor> MatrixXd;
typedef std::pair<int,int> Pair;
typedef std::map<std::pair<int,int>,double> Stencil;
typedef Eigen::Triplet<double> Triplet;
typedef Eigen::SparseMatrix<double,Eigen::RowMajor> SpMat;

const double epsilon= 1e-8;




#endif /* TYPEDEF_H_ */
