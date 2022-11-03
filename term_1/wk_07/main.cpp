#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <vector>
template <typename T>
struct Func
{
    virtual T operator()(T const_arr *, T) const = 0;
};

template <typename T>
struct Grav final : Func<int>
{
    T operator()(T const_arr *, T x) const override
    {
        return const_arr[0] * const_arr[0] * x;
    }
};

template <typename T>
struct Method
{
    virtual T df(T const_arr *, vector<T> value_arr) const = 0;
};

template <typename T>
struct Eiler
{
    virtual vector<T> df(T const_arr *, vector<T> value_arr, T delita, Func<T> f)
    {
        std::vector<T> result;
        result.push_back(value_arr[0] + delita * value_arr[1]);
        result.push_back(value_arr[1] + f(const_arr, value_arr[0]) * delita);
        return result;
    }
};
template <typename df, typename T>
class Calc
{
    Calc(T const_arr *, Func<T> f, Method<T> meth) : f(f), meth(meth)
    {
    }
    void process(T x_0, T v_0, T delita, int N)
    {
        x_arr.push_back(x_0);
        v_arr.push_back(v_0);
        for (int i = 0; i < N; ++i){

        }
    }

private:
    std::vector<T> = x_arr;
    std::vector<T> = v_arr;
    Func<T> f;
    Method<T> meth;
};
int main()
{
}