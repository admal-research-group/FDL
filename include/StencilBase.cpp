/*
 * StencilBase.cpp
 *
 *  Created on: Jun 16, 2020
 *      Author: Nikhil
 */

#include "StencilBase.h"
#include <utility>

template<typename Derived>
StencilBase<Derived>::StencilBase(const StencilTripletContainerType& stencilTripletContainer) :
		StencilTripletContainerType(stencilTripletContainer)
{

}

template<typename Derived>
StencilBase<Derived>::~StencilBase() {
	// TODO Auto-generated destructor stub
}

// Access the derived object
template<typename Derived>
Derived& StencilBase<Derived>::derived() { return *static_cast<Derived*>(this);}

template<typename Derived>
const Derived& StencilBase<Derived>::derived() const {return *static_cast<const Derived*>(this);}


