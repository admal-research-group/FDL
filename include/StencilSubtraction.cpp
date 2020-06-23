/*
 * StencilSubtractio.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#include "StencilSubtraction.h"
#include <string>

template<typename T1,typename T2>
StencilSubtraction<T1,T2>::StencilSubtraction(const StencilBase<T1>& op1,
											  const StencilBase<T2>& op2):
		StencilBase<StencilSubtraction<T1,T2>>(computeStencil(op1,op2)),
		op1(op1),
		op2(op2)
{

}

template<typename T1,typename T2>
typename StencilSubtraction<T1,T2>::StencilTripletContainerType StencilSubtraction<T1,T2>::computeStencil(const StencilTripletContainerType& v1,
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
			iter->second-=elem.second;
			if(std::fabs(iter->second)<FLT_EPSILON)
			{
				temp.erase(iter);
			}
		}
	}
	return temp;
}

template<typename T1,typename T2>
std::string StencilSubtraction<T1,T2>::tag() const
{
	return "StencilSubtraction";
}

template<typename T1,typename T2>
StencilSubtraction<T1,T2>::~StencilSubtraction()
{}
