#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include <stdio.h>
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

long long int factorial(const int n)
{
    long f = 1;
    for (int i = 1; i <= n; ++i)
        f *= i;
    return f;
}
int main(int argc, char *(argv[]))
{
    float start = std::atof(argv[1]);
    float end = std::atof(argv[2]);
    float delita = std::atof(argv[3]);
    unsigned long long int N = 100000;
    int n = abs(int((end - start) / delita));
    float *result = new float[n];
    float *true_result = new float[n];
    float *diff_result = new float[n];
    int *break_result = new int[n];
    std::cout.precision(9);
    float x = start;
    for (unsigned long long int i = 0; i < n; ++i)
    {
        int i_break = int(10 * (x + 1)) + int(10 * (x + 1)) % 2 + 1;
        float sum = 0;
        float slag = pow(-1, i_break) * pow(x, 2 * i_break + 1) / factorial(i_break);
        for (int j = i_break; j >= 1; j -= 2)
        {
            float temp = sum;
            sum += slag;
            slag *= -1 / x * (j - 1) / x * (j - 2);
            std::cout << std::scientific << sum << '\n';
            // if (nearlyEqual(sum, temp, 1e-15))
            // {
            //     // std::cout << "break due to stunting, i break " << j << '\n';
            //     break_result[i] = j;
            //     break;
            // }
            // if (i % 100000 == 0)
            // {
            //     std::cout << "I'm typing, now  " << i << "sum: " << sum << '\n';
            // }
        }
        result[i] = sum;
        true_result[i] = sin(x);
        diff_result[i] = fabs(sum - sin(x));
        std::cout << "x:" << x << " final result  " << std::scientific << sum << " true result: " << sin(x) << " diff: " << fabs(sum - sin(x)) << '\n';
        x += delita;
    }

    std::ofstream out("result.bin", std::ios::binary | std::ios::out);
    out.write((char *)result, n * sizeof(float));
    out.close();
    std::ofstream out_true("true_result.bin", std::ios::binary | std::ios::out);
    out_true.write((char *)true_result, n * sizeof(float));
    out_true.close();
    std::ofstream out_diff("diff_result.bin", std::ios::binary | std::ios::out);
    out_diff.write((char *)diff_result, n * sizeof(float));
    out_diff.close();
    std::ofstream out_break("break_result.bin", std::ios::binary | std::ios::out);
    out_break.write((char *)break_result, n * sizeof(int));
    out_break.close();
    delete[] diff_result;
    delete[] true_result;
    delete[] break_result;
    delete[] result;
    return 0;
}