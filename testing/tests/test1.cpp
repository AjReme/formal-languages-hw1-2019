#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("aa.a+a.a.a.", 'a', 3) == 4);
}
