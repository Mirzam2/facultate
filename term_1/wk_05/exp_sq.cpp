#include <iostream>
#include <cmath>
#include <limits>
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

    else if (a == 0 || b == 0 || diff < std::numeric_limits<float>::min())
    {
        // a or b is zero or both are extremely close
        // to it; relative error is less meaningful here
        return (diff < (eps * std::numeric_limits<float>::min()));
    }
    else
    {
        // use relative error
        return (diff / (absA + absB) < eps);
    }
}
double func(double &x)
{
    return exp(-x * x);
}
int main()
{
    unsigned int N = 1000000;
    double delita = 0.001;
    double sum = 0;
    double x = 0;
    std::cout.precision(15);
    for (int i = 0; i < N; ++i)
    {
        double temp = sum;
        sum += func(x) * delita;
        if (nearlyEqual(sum, temp, 1e-15))
        {
            std::cout << "break due to stunting, i break " << i << " ,x break: " << std::scientific << x << '\n';
            break;
        }
        // std::cout << std::scientific << sum << '\n';
        x += delita;
    }

    std::cout << "final result square: " << std::scientific << sum << '\n';
    return 0;
}