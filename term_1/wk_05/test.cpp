#include <float.h>
#include <iostream>
#include <cmath>
// compiler-dependent,

// may be in a non-standard location

int nearlyEqual(float a, float b, float eps)

{

    float absA = std::fabs(a);

    float absB = std::fabs(b);

    float diff = std::fabs(a - b);

    if (a == b)

    {

        // shortcut, handles infinities

        return true;
    }

    else if (a == 0 || b == 0 || diff < FLT_MIN)
    {
        // a or b is zero or both are extremely close
        // to it; relative error is less meaningful here
        return (diff < (eps * FLT_MIN));
    }
    else
    {
        // use relative error
        return (diff / (absA + absB) < eps);
    }
}
int main(){
    std::cout << FLT_MIN;
}
