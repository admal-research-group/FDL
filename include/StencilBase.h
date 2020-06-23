/*
 * StencilBase.h
 *
 *  Created on: Jun 16, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_STENCILBASE_H_
#define INCLUDE_STENCILBASE_H_

#include <map>
#include <cmath>


template<typename Derived>
class StencilBase : public std::map<std::pair<int,int>,double>
{
public:
    typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;

	StencilBase(const StencilTripletContainerType&);
	// Access the derived object
	Derived& derived();
	const Derived& derived() const ;

	template<typename T>
	friend T& operator << (T& os, const StencilBase<Derived>& st)
	{
		os  << st.derived().tag()<<" stencil:\n";
		for(const auto& elem : st)
		{
			os<< elem.first.first<<" "<<elem.first.second<<" "<<elem.second<<"\n";
		}
		return os;
	}

	virtual ~StencilBase();

};
#include "StencilBase.cpp"

#endif /* INCLUDE_STENCILBASE_H_ */
