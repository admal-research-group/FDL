#include <iostream>
#include <map>
#include <tuple>
#include <cmath>
#include <cfloat>
#include <string>
#include <LDO.h>

#include "Diff.h"
#include "Stencil.h"

int main()
{
    Function f;
    
//    std::cout<<f<<std::endl;
//
//    std::cout<<backDiff(f,0)<<std::endl;
//    std::cout<<backDiff(backDiff(f,0),0)<<std::endl;
//
//    std::cout<<centerDiff(f,0)<<std::endl;
//    std::cout<<centerDiff(centerDiff(f,0),0)<<std::endl;
//
//
//    std::cout<<f+f<<std::endl;
//    std::cout<<3.0*(f+f)<<std::endl;
//    std::cout<<f-f<<std::endl;

    auto g(1.0*(f+f)+f+centerDiff(f,0));
    std::cout<<g<<std::endl;

    LDO l;
    //diff(f,2,3) = centerDiff(centerDiff(centerDiff(centerDiff(f,0),0),1),1)
    return 0;
}
