#include <iostream>
#include <cmath>
int main()
{
    unsigned long long int N = 1e9;
    float sum = 0;
    std::cout.precision(9);
    for (unsigned long long int i = N; i > 0; i--)
    {
        //float temp = sum;
        sum += 1. / i;
        // std::cout << std::scientific << sum << '\n';
        // if (fabsf(sum - temp) / sum < 1e-9)
        // {
        //     std::cout << "break due to stunting, i break " << i << '\n';
        //     break;
        // }
        if (i % 100000 == 0){
            std::cout << "I'm typing, now  " << i  << "sum: "  << sum << '\n';
        }
    }

    std::cout << "final result  " << std::scientific << sum << '\n';
    return 0;
}