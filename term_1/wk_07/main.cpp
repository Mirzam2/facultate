#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <vector>
template <typename T>
struct Func
{
    virtual T operator()(T *const_arr, T) const = 0;
};

template <typename T>
struct Grav final : Func<int>
{
    T operator()(T *const_arr, T x) const override
    {
        return const_arr[0] * const_arr[0] * x;
    }
};

template <typename T>
struct Method
{
    virtual T df(T *const_arr, std::vector<T> value_arr, T delita, Func<T> f) const = 0;
};

template <typename T>
struct Eiler
{
    std::vector<T> df(T *const_arr, std::vector<T> value_arr, T delita, Func<T> f) override
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
    Calc(T *const_arr, Func<T> f, Method<T> meth) : f(f), meth(meth), const_arr(const_arr)
    {
    }
    void process(std::vector<T> start_value, T delita, int N)
    {
        value_arr.push_back(start_value);
        for (int i = 0; i < N; ++i)
        {
            value_arr.push_back(meth.df(const_arr, value_arr[i], delita, f));
        }
    }

private:
    T *const_arr;
    std::vector<std::vector<T>> value_arr;
    Func<T> f;
    Method<T> meth;
};
int main()
{
}