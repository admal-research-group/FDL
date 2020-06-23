/*
 * StencilPro.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_STENCILPROD_H_
#define INCLUDE_STENCILPROD_H_

#include "StencilBase.h"

template<typename T>
class StencilProd : public StencilBase<StencilProd<T>>
{
public:
    typedef typename StencilBase<StencilProd<T>>::StencilTripletContainerType StencilTripletContainerType;

    const double& op1;
    const StencilBase<T>& op2;

    StencilProd(const double&, const StencilBase<T>&);

    static StencilTripletContainerType computeStencil(const double&,const StencilTripletContainerType&);

    std::string tag() const;
	virtual ~StencilProd();
};

template<typename T>
StencilProd<T> operator*(const double& op1,const StencilBase<T>& op2)
{
    return StencilProd<T>(op1,op2);
}

template<typename T>
StencilProd<T> operator*(const StencilBase<T>& op2,const double& op1)
{
    return StencilProd<T>(op1,op2);
}
#include "StencilProd.cpp"
#endif /* INCLUDE_STENCILPROD_H_ */
