/*
 * Function.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_FUNCTION_H_
#define INCLUDE_FUNCTION_H_

#include "StencilBase.h"

class Function : public StencilBase<Function>// 0,0,1
{
public:
    typedef typename StencilBase<Function>::StencilTripletContainerType StencilTripletContainerType;


	Function() : StencilBase<Function>(StencilTripletContainerType{{std::make_pair(0,0),1.0}})
	{

	}

    std::string tag() const
    {
        return "Function";
    }

};






#endif /* INCLUDE_FUNCTION_H_ */
