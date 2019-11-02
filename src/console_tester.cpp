#include <string>
#include <iostream>
#include "solver.hpp"


int main() {
    std::string a;
    char x;
    size_t k;
    std::cin >> a >> x >> k;
    std::cout << solver(a, x, k).solve() << '\n';
}