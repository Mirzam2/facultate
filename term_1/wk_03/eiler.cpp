#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
int main(int argc, char *(argv[]))
{
    float w = std::atof(argv[1]);
    float x_0 = std::atof(argv[2]);
    float v_0 = std::atof(argv[3]);
    unsigned long int N = std::atoi(argv[4]); //насколько разбиваем
    std::cout << w << " " << x_0 << " " << v_0 << " " << N;
    float delita_x = std::atof(argv[4]);
    float *x_array = new float[N];
    float *x_abs = new float[N];
    float *v_array = new float[N];
    float *E_array = new float[N];
    x_array[0] = x_0;
    x_abs[0] = x_0;
    v_array[0] = v_0;
    E_array[0] = v_0 * v_0 / 2 + x_0 * x_0 * w / 2;
    std::ofstream out("results_x.bin", std::ios::binary | std::ios::out);
    for (int i = 0; i < N; ++i)
    {
        x_abs[i + 1] = x_0 * cos(i * delita_x);
        x_array[i + 1] = x_array[i] + delita_x * v_array[i];
        v_array[i + 1] = v_array[i] - delita_x * w * w * x_array[i];
        E_array[i + 1] = v_array[i + 1] * v_array[i + 1] / 2 + x_array[i + 1] * x_array[i + 1] * w / 2;

        // std::cout << x_array[i] << " "<< v_array[i] << '\n';
    }
    out.write((char *)x_array, N * sizeof(float));
    out.close();
    std::ofstream out_v("results_v.bin", std::ios::binary | std::ios::out);
    out_v.write((char *)v_array, N * sizeof(float));
    out_v.close();
    std::ofstream out_abs("results_x_abs.bin", std::ios::binary | std::ios::out);
    out_abs.write((char *)x_abs, N * sizeof(float));
    out_abs.close();
    std::ofstream out_E("results_E.bin", std::ios::binary | std::ios::out);
    out_E.write((char *)E_array, N * sizeof(float));
    out_E.close();
    delete[] x_array;
    delete[] v_array;
    delete[] x_abs;
    delete[] E_array;
    return 0;
}