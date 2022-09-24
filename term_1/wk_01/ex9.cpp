#include <iostream>
int main(){
    int n = 0;
    std::cin >> n;
    std::cout.setf(std::ios::scientific);
    double *array = new double[n];
    for (int i = 1; i <= n;++i){
        array[i-1] = 1.0 / i;
    }
    for (int i = 0; i < n; ++i){
        std::cout << array[i] << " ";
    }
    return 0;
}