#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <array>

template <typename T, std::size_t N>
class State
{
public:
    virtual int get_size() = 0;
    virtual void print() = 0;
    virtual T &operator[](int i) = 0;
    virtual void copy(State<T, N> &other){};

private:
};

template <typename T, std::size_t N>
class NVector final : public State<T, N>
{
public:
    NVector()
    {
        value = {};
    }
    void print() override
    {
        for (int i = 0; i < N; ++i)
        {
            std::cout << value[i] << " ";
        }
        std::cout << '\n';
    }
    NVector(const NVector<T, N> &other)
    {
        // std::cout << "copy called\n";
        for (int i = 0; i < N; ++i)
        {
            value[i] = other.value[i];
            // std::cout << this->value[i] << " " << other.value[i] << '\n';
        }
        print();
    }

    friend void swap(NVector<T, N>& a, NVector<T, N>& b){
        std::swap(a.value, b.value);
    }

    void copy(NVector<T, N> &other) 
    {   
        value = other.value;
    }
    // NVector operator=(const NVector<T, N> &other)
    // {
    //     value = other.value;
    //     return *this;
    // }
    int get_size() override { return N; }
    // void swap(State<T, N> &other) override
    // {
    //     std::swap(value, other.value);
    // };
    T &operator[](int i) override
    {
        return value[i];
    }

private:
    std::array<T, N> value;
};

template <typename T, std::size_t N>
class Func
{
public:
    virtual void operator()(State<T, N> &x, State<T, N> &result) = 0;

protected:
    std::vector<T> const_arr;
};

template <typename T, std::size_t N>
class Grav final : public Func<T, N>
{
public:
    Grav(std::vector<T> const_arr) : const_arr(const_arr) {}
    void operator()(State<T, N> &x, State<T, N> &result) override
    {
        result[0] = x[1];
        result[1] = -const_arr[0] * const_arr[0] * x[0];
    }

protected:
    std::vector<T> const_arr;
};
// template <typename T>
// struct pendum final : Func<T>
// {
//     T operator()(std::vector<T> const_arr, T x) override
//     {
//         return -sin(x);
//     }
// };

template <typename T, std::size_t N>
struct Method
{
    virtual void df(State<T, N> &value_arr, State<T, N> &result, State<T, N> &temp, T delita, Func<T, N> &f) = 0;
};

template <typename T, std::size_t N>
struct Eiler : Method<T, N>
{
    void df(State<T, N> &value_arr, State<T, N> &result, State<T, N> &temp, T delita, Func<T, N> &f) override
    {
        f(value_arr, temp);
        for (int i = 0; i < N; ++i)
        {
            result[i] = value_arr[i] + delita * temp[i];
            // std::cout << "test: " << result[i] << " " << temp[i] << '\n';
        }
    }
};
// // template <typename T>
// // struct Trap : Method<T>
// // {
// //     void df(std::vector<T> const_arr, State &value_arr, State &result, T delita, Func<T> &f) override
// //     {
// //         std::vector<T> temp;
// //         Eiler<T> eiler;
// //         temp = eiler.df(const_arr, value_arr, delita, f);
// //         result.push_back(value_arr[0] + delita * (temp[1] + value_arr[1]) / 2);
// //         result.push_back(value_arr[1] + delita * f(const_arr, ((temp[0] + value_arr[0]) / 2)));
// //         return result;
// //     }
// // };
template <typename T, std::size_t N>
class Calc
{
public:
    Calc(Func<T, N> &f, Method<T, N> &meth) : f(f), meth(meth)
    {
    }
    void process(State<T, N> &start_value, State<T, N> &end, State<T, N> &temp, T delita, int N_calc)
    {
        std::cout << "calculate start\n";
        for (int i = 0; i < N_calc; ++i)
        {
            std::cout << "i: " << i << " begin \n";
            start_value.print();
            end.print();
            meth.df(start_value, end, temp, delita, f);
            start_value.print();
            end.print();
            start_value.copy(end);
            std::cout << "i: " << i << " end\n";
            start_value.print();
            end.print();
        }
        // save_to_file(0, "aaao");
    }
    // void print()
    // {
    //     for (int i = 0; i < value_arr.size(); ++i)
    //     {
    //         std::cout << "i: " << i << " ";
    //         for (int j = 0; j < (value_arr[i]).size(); ++j)
    //         {
    //             std::cout << " " << j << " derevtive: " << value_arr[i][j];
    //         }
    //         std::cout << '\n';
    //     }
    // }
    void save_all_data()
    {
    }

private:
    T *x_arr;
    Func<T, N> &f;
    Method<T, N> &meth;
    // void save_to_file(int index, std::string name)
    // {
    //     name += ".bin";
    //     std::ofstream out(name, std::ios::binary | std::ios::out);
    //     for (int i = 0; i < value_arr.size(); ++i)
    //     {
    //         out.write((char *)value_arr[i][index], sizeof(T));
    //     }
    //     out.close();
    // }
};
int main()
{
    std::vector<float> const_arr;
    NVector<float, 2> start;
    NVector<float, 2> end;
    start.print();

    start[0] = 1;
    start[1] = 0;

    std::cout << " prior swap" << std::endl;
    start.print();
    end.print();

    std::cout << " swap done here" << std::endl;
    std::swap(start, end);

    std::cout << " upon swap" << std::endl;
    start.print();
    end.print();
    // please refer to the https://stackoverflow.com/questions/20594374/c-inheritance-of-copy-move-swap-assignment-and-destructor-which-do-i-need
    std::cout << "please refer https://stackoverflow.com/questions/20594374/c-inheritance-of-copy-move-swap-assignment-and-destructor-which-do-i-need for more info" << std::endl;
    return 0;

    const_arr.push_back(1);
    NVector<float, 2> t(start);
    end.copy(start);
    std::cout << "copy t test\n";
    start.print();
    end.print();
    t.print();
    Grav<float, 2> fu(const_arr);
    Eiler<float, 2> eil;
    eil.df(start, end, t, 0.1, fu);
    start.copy(end);
    eil.df(start, end, t, 0.1, fu);
    std::cout << "df test: \n";
    start.print();
    end.print();
    //     // Grav<float> fu;
    Calc<float, 2> calculate(fu, eil);
    calculate.process(start, end, t, 0.1, 10);
    start.print();
    //      // calculate.process(start, 0.01, 100);
    //      // calculate.print();
    return 0;
}
