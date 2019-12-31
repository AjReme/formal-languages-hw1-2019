#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("aa.a.aa.a+.", 'a', 4) == 4);
}
