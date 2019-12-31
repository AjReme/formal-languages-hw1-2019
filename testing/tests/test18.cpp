#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("ab+c.aba.*.bac.+.+*", 'b', 2) == 4);
}
