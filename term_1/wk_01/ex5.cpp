#include <iostream>
#include <fstream>
int main(){
    int n = 0;
    std::cin >> n;
    std::ofstream file("ex5.txt");
    for (int i = 1; i <= n;i++){
        file << i << " ";
    }
    file.close();
    return 0;
}