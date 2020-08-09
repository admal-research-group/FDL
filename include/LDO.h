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
public:
	typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;
	void appendStencil(StencilTripletContainerType& containerIn)
	{
		// append stencilTripletContainer to containerIn
		static_cast<T*>(this)->appendStencil(containerIn);
	}
	void appendStencil(StencilTripletContainerType& containerIn) const
	{
		// append stencilTripletContainer to containerIn
		static_cast<const T*>(this)->appendStencil(containerIn);
	}
	T& derived()
	{
		return *static_cast<T*>(this);
	}
	const T& derived() const
	{
		return *static_cast<const T*>(this);
	}

};

class LDO : public LDOExpression<LDO>
{
public:
	typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;

	StencilTripletContainerType stencilTripletContainer;

	// Construct LDO from a stencil
	explicit LDO(StencilTripletContainerType stencilTripletContainer) :
		stencilTripletContainer(stencilTripletContainer){}

	// Construct LDO from an expression
	template<typename T>
	explicit LDO(const LDOExpression<T>& expr)
	{
		expr.appendStencil(stencilTripletContainer);
	}

	void displayTag()
	{
		std::cout << "LDO" << std::endl;
	}
	void displayTag() const
	{
		std::cout << "LDO" << std::endl;
	}
	StencilTripletContainerType& appendStencil(StencilTripletContainerType& containerIn)
	{
		// append stencilTripletContainer to containerIn
		for (auto elem : stencilTripletContainer)
		{
			auto iter(containerIn.find(elem.first));
			if (iter==containerIn.end())
			{// key not found
				if(std::fabs(elem.second)>FLT_EPSILON)
				{
					containerIn.emplace(elem);
				}
			}
			else
				iter->second= iter->second + elem.second;
		}
		return containerIn;
	}
	StencilTripletContainerType& appendStencil(StencilTripletContainerType& containerIn) const
	{
		// append stencilTripletContainer to containerIn
		for (auto elem : stencilTripletContainer)
		{
			auto iter(containerIn.find(elem.first));
			if (iter==containerIn.end())
			{// key not found
				if(std::fabs(elem.second)>FLT_EPSILON)
				{
					containerIn.emplace(elem);
				}
			}
			else
				iter->second= iter->second + elem.second;
		}
		return containerIn;
	}

	template<typename T>
	friend T& operator << (T& os, const LDO& ldo)
	{
		ldo.displayTag();
		for(const auto& elem : ldo.stencilTripletContainer)
		{
			os<< elem.first.first<<" "<<elem.first.second<<" "<<elem.second<<"\n";
		}
		return os;
	}
};

// LDOSum
template<typename T1, typename T2>
class LDOSum : public LDOExpression<LDOSum<T1,T2>>
{
public:
	typedef std::map<std::pair<int,int>,double> StencilTripletContainerType;
	const T1& op1;
	const T2& op2;

	explicit LDOSum(const T1& op1, const T2& op2) : op1(op1),op2(op2){}

	void appendStencil(StencilTripletContainerType& containerIn)
	{
		// append stencilTripletContainers of op1 and op2 to containerIn
		// pass the container to op 1 and then to op2
		op1.appendStencil(containerIn);
		op2.appendStencil(containerIn);
	}

	void appendStencil(StencilTripletContainerType& containerIn) const
	{
		// append stencilTripletContainers of op1 and op2 to containerIn
		// pass the container to op 1 and then to op2
		op1.appendStencil(containerIn);
		op2.appendStencil(containerIn);
	}
	void displayTag()
	{
		std::cout << "LDOSum" << std::endl;
	}
	void displayTag() const
	{
		std::cout << "LDOSum" << std::endl;
	}
};

template<typename T1, typename T2>
LDOSum<T1,T2> operator + (const LDOExpression<T1>& op1, const LDOExpression<T2>& op2)
{
	return LDOSum<T1,T2> (op1.derived(),op2.derived());
}



#endif /* INCLUDE_LDO_H_ */
