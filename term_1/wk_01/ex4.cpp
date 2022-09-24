#include <iostream>
#include <fstream>
int main(){
    std::ofstream file("ex4.txt");
    for (int i = 1; i <= 30;i++){
        file << i << " ";
    }
    file.close();
    return 0;
}