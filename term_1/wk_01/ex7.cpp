#include <iostream>
#include <fstream>
int main(int argc, char *(argv[]))
{
    std::ofstream file("ex7.txt");
    int n = std::atoi(argv[1]);
    std::cout << n;
    unsigned long long a = 1;
    unsigned long long b = 1;
    if (n == 1)
    {
        file << 1 << "     " << 1 << '\n';
    }
    else
    {
        file << 1 << "     " << 1 << '\n';
        file << 2 << "     " << 1 << '\n';

        for (int i = 1; i <= n; i++)
        {
            a = b + a;

            file << i << "     " << a << '\n';
            unsigned long long temp = b;
            b = a;
            a = temp;
        }
    }
    file.close();
    return 0;
}