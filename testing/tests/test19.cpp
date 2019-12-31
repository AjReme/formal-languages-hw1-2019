#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("acb..bab.c.*.ab.ba.+.+*a.", 'b', 3) == 7);
}
