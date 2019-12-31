#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("ba.a.ab.b.+*", 'a', 3) == 6);
}
