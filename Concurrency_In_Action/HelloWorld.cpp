//
// Created by Kumar Chakravarthy on 09-Nov-23.
//
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    std::thread t(hello);
    t.join();

    return 0;
}
