#include <iostream>
#include <map>
#include <tuple>
#include <cmath>
#include <cfloat>
#include <string>
#include <LDO.h>
#include <Function.h>


int main()
{
    Function f;

    // construct LDO from expression
    LDO le(f+f+f);
    //default copy constructor
    LDO l(le);


    std::cout << le << std::endl;
    return 0;
}
