#include "solver.hpp"


int main() {
	exit(solve("ab+c.aba.*.bac.+.+*", 'b', 2) != 4);
}
