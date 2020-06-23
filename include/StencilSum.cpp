/*
 * StencilSum.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#include "StencilSum.h"
#include <cmath>


template<typename T1, typename T2>
StencilSum<T1,T2>::StencilSum(const StencilBase<T1>& op1_in, const StencilBase<T2>& op2_in):
     StencilBase<StencilSum<T1,T2>>(computeStencil(op1_in,op2_in)),
	 op1(op1_in),
	 op2(op2_in)
{

}

template<typename T1, typename T2>
typename StencilSum<T1,T2>::StencilTripletContainerType StencilSum<T1,T2>::computeStencil(const StencilTripletContainerType& v1,
																		  const StencilTripletContainerType& v2)
{
	StencilTripletContainerType temp(v1);
	for(const auto& elem : v2)
	{
		auto iter(temp.find(elem.first));
		if(iter==temp.end())
		{// key not found
			if(std::fabs(elem.second)>FLT_EPSILON)
			{
				temp.emplace(elem);
			}
		}
		else
		{
			iter->second+=elem.second;
			if(std::fabs(iter->second)<FLT_EPSILON)
			{
				temp.erase(iter);
			}
		}
	}
	return temp;
}


template<typename T1, typename T2>
std::string StencilSum<T1,T2>::tag() const
{
	return "StencilSum";
}


template<typename T1,typename T2>
StencilSum<T1,T2>::~StencilSum() {
	// TODO Auto-generated destructor stub
}

