#include <iostream>
#include <cmath>
int main()
{
    float N = 100;
    float sum = 0;
    std::cout.precision(15);
    for (int i = 0; i < N; ++i)
    {
        sum += powf(2, -i);
        std::cout << std::scientific << sum << '\n';
    }

    std::cout << std::scientific << sum << '\n';
    return 0;
}