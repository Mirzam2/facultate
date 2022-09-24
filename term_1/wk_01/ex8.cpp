#include <iostream>
#include <array>
int main(int argc, char *(argv[]))
{
    const int n = std::atoi(argv[1]);
    std::array<long long, 40> massiv = {};
    long long a = 1;
    long long b = 1;
    if (n == 1)
    {
        massiv[0] = 1;
    }
    else
    {
        massiv[0] = 1;
        massiv[1] = 1;
        for (int i = 2; i < n; i++)
        {
            a = b + a;
            std::cout << a << " ";
            massiv[i] = a;
            unsigned long long temp = b;
            b = a;
            a = temp;
        }
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << massiv[i] << " ";
    }
    return 0;
}