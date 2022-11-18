#include <iostream>
#include <cmath>
int main()
{
    unsigned long long int N = 1e12;
    double sum = 0;
    std::cout.precision(9);
    for (unsigned long long int i = 1; i < N; ++i)
    {
        double temp = sum;
        sum += 1. / i;
        //std::cout << std::scientific << sum << '\n';
        if (fabsf(sum - temp) < 1e-15)
        {
            std::cout << "break due to stunting, i break " << i << '\n';
            break;
        }
        if (i % 100000 == 0){
            std::cout << "I'm typing, now  " << i  << "sum: "  << sum << '\n'; 
        }
    }

    std::cout << "final result  " << std::scientific << sum << '\n';
    return 0;
}