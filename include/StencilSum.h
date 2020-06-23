/*
 * StencilSum.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_STENCILSUM_H_
#define INCLUDE_STENCILSUM_H_

#include "StencilBase.h"

template<typename T1,typename T2>
class StencilSum : public StencilBase<StencilSum<T1,T2>>
{
public:
    typedef typename StencilBase<StencilSum<T1,T2>>::StencilTripletContainerType StencilTripletContainerType;
    const StencilBase<T1>& op1;
    const StencilBase<T2>& op2;

    StencilSum(const StencilBase<T1>&, const StencilBase<T2>&);

    static StencilTripletContainerType computeStencil(const StencilTripletContainerType&,
                                                      const StencilTripletContainerType&);

    std::string tag() const;
	virtual ~StencilSum();
};

template<typename T1,typename T2>
StencilSum<T1,T2> operator+(const StencilBase<T1>& op1,const StencilBase<T2>& op2)
{
    return StencilSum<T1,T2>(op1,op2);
}
#include "StencilSum.cpp"


#endif /* INCLUDE_STENCILSUM_H_ */
