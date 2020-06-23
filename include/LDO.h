/*
 * LDO.h
 *
 *  Created on: Jun 23, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_LDO_H_
#define INCLUDE_LDO_H_

#include <map>

template<typename T>
class LDOExpression
{
	typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;
	const StencilTripletContainerType& stecil()
	{
		return static_cast<T*>(this)->stencil();

	}
	T& derived()
	{
		return *static_cast<T*>(this);
	}
	const T& derived() const
	{
		return *static_cast<const T&>(this);
	}
};
class LDO : public LDOExpression<LDO>
{
public:
	typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;
	StencilTripletContainerType stencilTripletContainer;

	const StencilTripletContainerType& stencil();

	LDO(){}
	template<typename T>
	LDO(const LDOExpression<T>& expr)
	{
		stencilTripletContainer= expr.stencil();

	}



};




#endif /* INCLUDE_LDO_H_ */
