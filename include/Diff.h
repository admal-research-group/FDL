/*
 * Diff.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Nikhil
 */

#ifndef INCLUDE_DIFF_H_
#define INCLUDE_DIFF_H_

#include "StencilBase.h"

struct BackDiff
{
    static const std::map<int,double> shifts;

    static std::string tag()
    {
        return "BackDiff";
    }

};
const std::map<int,double> BackDiff::shifts{{0,1.0},{-1,-1.0}};

struct CenterDiff
{
    static const std::map<int,double> shifts;

    static std::string tag()
    {
        return "CenterDiff";
    }
};
const std::map<int,double> CenterDiff::shifts{{1,0.5},{-1,-0.5}};



template<typename T,typename Type>
struct Diff : public StencilBase<Diff<T,Type>>
{

    typedef typename StencilBase<Diff<T,Type>>::StencilTripletContainerType StencilTripletContainerType;


    const StencilBase<T>& op;

    Diff(const StencilBase<T>& op_in,const int& dir):
    /* init */ StencilBase<Diff<T,Type>>(computeStencil(op_in,dir))
    /* init */,op(op_in)
    {

    }

    static StencilTripletContainerType computeStencil(const StencilTripletContainerType& v,const int& dir)
    {
        StencilTripletContainerType temp;
        for(const auto& elem : v)
        {
            for(const auto s : Type::shifts)
            {
                std::pair<int,int> ij(dir==0? std::make_pair(elem.first.first+s.first,elem.first.second) : std::make_pair(elem.first.first,elem.first.second+s.first));
                auto iter(temp.find(ij));
                if(iter==temp.end())
                {// key not found
                    if(std::fabs(elem.second)>FLT_EPSILON)
                    {
                        temp.emplace(ij,elem.second*s.second);
                    }
                }
                else
                {
                    iter->second+=elem.second*s.second;
                    if(std::fabs(iter->second)<FLT_EPSILON)
                    {
                        temp.erase(iter);
                    }
                }
            }
        }

        return temp;
    }

    std::string tag() const
    {
        return Type::tag();
    }
};

template<typename T>
Diff<T,BackDiff> backDiff(const StencilBase<T>& op1,const int& dir)
{
    return Diff<T,BackDiff>(op1,dir);
}

template<typename T>
Diff<T,CenterDiff> centerDiff(const StencilBase<T>& op1,const int& dir)
{
    return Diff<T,CenterDiff>(op1,dir);
}






#endif /* INCLUDE_DIFF_H_ */
