#include <cassert>
#include "solver.hpp"

int main() {
    assert(solve("aa.*a.", 'a', 3) == 3);
}
