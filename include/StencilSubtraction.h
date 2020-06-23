/*
 * StencilSubtractio.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_STENCILSUBTRACTION_H_
#define INCLUDE_STENCILSUBTRACTION_H_
#include "StencilBase.h"

template<typename T1,typename T2>
class StencilSubtraction  : public StencilBase<StencilSubtraction<T1,T2>> {
public:
    typedef typename StencilBase<StencilSubtraction<T1,T2>>::StencilTripletContainerType StencilTripletContainerType;
    const StencilBase<T1>& op1;
    const StencilBase<T2>& op2;

    StencilSubtraction(const StencilBase<T1>&, const StencilBase<T2>&);
    static StencilTripletContainerType computeStencil(const StencilTripletContainerType&, const StencilTripletContainerType&);
    std::string tag() const;
	virtual ~StencilSubtraction();
};


template<typename T1,typename T2>
StencilSubtraction<T1,T2> operator-(const StencilBase<T1>& op1,const StencilBase<T2>& op2)
{
    return StencilSubtraction<T1,T2>(op1,op2);
}
#include "StencilSubtraction.cpp"
#endif /* INCLUDE_STENCILSUBTRACTION_H_ */

