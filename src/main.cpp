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
    //LDO le(f+f+f);
    //default copy constructor
    //LDO l(le);

    auto g= f+f+f;
    //LDO g= f+f+f;
    //LDOSum<LDO,LDO> g= f+f;


    // should display LDOSum
    g.displayTag();

    // why is the following working?
    // g is not an LDO, it is LDOSum<T1,T2>.
    // Yet the friend function which accepts g
    // using a const LDO reference gets executed. Why is it possible to
    // pass a LDOSum<T1,T2> to a
    // function that accepts a LDO reference?
    std::cout << g << std::endl;
    return 0;
}
