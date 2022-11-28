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
    friend void swap(State<T, N> &a, State<T, N> &b){};
    virtual std::array<T, N> get_array() = 0;
    virtual State& operator()(){return *this;}

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
        std::cout << std::endl;
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
    // NVector& operator()()
    // {
    //     return new NVector<T, N>();
    // }
    friend void swap(NVector<T, N> &a, NVector<T, N> &b)
    {
        std::swap(a.value, b.value);
    }

    void copy(NVector<T, N> &other)
    {
        value = other.value;
    }
    std::array<T, N> get_array()
    {
        return value;
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
#include <memory>
template <class NV>
class Fabric
{
public:
    NV fabric(){
        return NV();
    }
};
template <typename T, std::size_t N>
class Func
{
public:
    virtual void operator()(State<T, N> &x, State<T, N> &result) = 0;
    virtual float energy(State<T, N> &data) = 0;

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
    float energy(State<T, N> &x) override
    {
        return x[1] * x[1] / 2 - const_arr[0] * x[0];
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

template <typename T, std::size_t N, typename NV>
struct Method
{
    virtual void df(State<T, N> &value_arr, State<T, N> &result, State<T, N> &temp, T delita, Func<T, N> &f, Fabric<NV>& fab) = 0;
};

template <typename T, std::size_t N,typename NV>
struct Eiler : Method<T, N,NV>
{
    void df(State<T, N> &value_arr, State<T, N> &result, State<T, N> &temp, T delita, Func<T, N> &f, Fabric<NV>& fab) override
    {
        f(value_arr, temp);
        for (int i = 0; i < N; ++i)
        {
            result[i] = value_arr[i] + delita * temp[i];
            // std::cout << "test: " << result[i] << " " << temp[i] << '\n';
        }
    }
};
template <typename T, std::size_t N, typename NV>
struct RungeKyt : Method<T, N,NV>
{
    void df(State<T, N> &value, State<T, N> &result, State<T, N> &temp, T delita, Func<T, N> &f,Fabric<NV>& fab) override
    {
        f(value,temp);
        auto k1 = fab.fabric();
        auto k2 = fab.fabric();
        auto k3 = fab.fabric();
        auto k4 = fab.fabric();
        auto YY = fab.fabric();

        f(value,k1);

        for (int i =0; i < N; ++i){
            YY[i] = value[i] + k1[i] * delita /2;
        }
        f(YY,k2);
        for (int i =0; i < N; ++i){
            YY[i] = value[i] + k2[i] * delita /2;
        }
        f(YY,k3);
        for (int i =0; i < N; ++i){
            YY[i] = value[i] + k3[i] * delita;
        }
        f(YY,k4);
        for (int i =0; i < N; ++i){
            result[i] = value[i] + delita / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
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


template <typename T, std::size_t N, class NV>
class Calc
{
public:
    Calc(Func<T, N> &f, Method<T, N,NV> &meth, Fabric<NV>& fab) : f(f), meth(meth), fab(fab)
    {
    }
    void process(State<T, N> *start_value, State<T, N> *end, State<T, N> *temp, T delita, int N_calc )
    {
        std::cout << "calculate start\n";
        for (int i = 0; i < N_calc; ++i)
        {
            meth.df(*start_value, *end, *temp, delita, f, fab);
            temp = start_value;
            start_value = end;
            end = temp;
            // std::cout << "i: " << i << " end\n";
            // start_value->print();
            // end->print();
            // auto ter = start_value->operator()();
            std::array<T, N> t = end->get_array();
            data.push_back(t);
        }
        std::cout << "calculate end\n";
        save_to_file("data.txt");
    }
    void save_to_file(std::string filename)
    {
        std::ofstream f;
        f.open(filename);
        for (int i = 0; i < data.size(); ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                f << data[i][j] << "\t";
            }

            f << "\n";
        }

        f.close();
    }

private:
    std::vector<std::array<T, N>> data;
    T *x_arr;
    Func<T, N> &f;
    Method<T, N,NV> &meth;
    Fabric<NV> &fab;
};
int main(int argc, char *(argv[]))
{
    //на вход подается колво шагов и шаг, x0,v0
    size_t N = std::atoi(argv[1]);
    float del = std::atof(argv[2]);
    std::vector<float> const_arr;
    NVector<float, 2> start;
    NVector<float, 2> end;
    //можно написать универсальную принимающую из python циклом по количеству аргументов
    start[0] = std::atof(argv[3]);
    start[1] = std::atof(argv[4]);
    // please refer to the https://stackoverflow.com/questions/20594374/c-inheritance-of-copy-move-swap-assignment-and-destructor-which-do-i-need
    
    
    const_arr.push_back(1);
    NVector<float, 2> t(start);
    Grav<float, 2> fu(const_arr);
    RungeKyt<float, 2,NVector<float,2>> rk;
    Eiler<float, 2,NVector<float,2>> eil;
    Fabric<NVector<float,2>> fab;
    Calc<float, 2,NVector<float,2>> calculate(fu, rk,fab);
    calculate.process(&start, &end, &t, del, N);
    start.print();
    //      // calculate.process(start, 0.01, 100);
    //      // calculate.print();
    return 0;
}
