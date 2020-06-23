/*
 * StencilPro.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#include "StencilProd.h"

template<typename T>
StencilProd<T>::StencilProd(const double& op1,
               const StencilBase<T>& op2):
    /* init */ StencilBase<StencilProd<T>>(computeStencil(op1,op2))
    /* init */,op1(op1)
    /* init */,op2(op2)
    {

    }

template<typename T>
typename StencilProd<T>::StencilTripletContainerType StencilProd<T>::computeStencil(const double& s, const StencilTripletContainerType& v)
{
	if(std::fabs(s)<FLT_EPSILON)
	{
		return StencilTripletContainerType();
	}
	else
	{
		StencilTripletContainerType temp;
		for(const auto& elem : v)
		{
			const double newVal(s*elem.second);

			if(std::fabs(newVal)>FLT_EPSILON)
			{
				temp.emplace(elem.first,newVal);
			}

		}
		return temp;
	}
}

template<typename T>
std::string StencilProd<T>::tag() const
{
	return "StencilProd";
}

template<typename T>
StencilProd<T>::~StencilProd() {
}

