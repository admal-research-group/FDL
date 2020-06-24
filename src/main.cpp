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
    auto le(f+f+f);
    LDO l(le);

    std::cout << l << std::endl;
    return 0;
}
