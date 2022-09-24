#include <iostream>
#include <fstream>
int main (int argc, char*(argv[])){
    std::ofstream file("ex6.txt");
    int n = std::atoi( argv[1]);
    std::cout << n;
    for (int i = 1; i <= n;i++){
        file << i << " ";
    }
    file.close();
    return 0;
}