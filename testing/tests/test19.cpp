#include "solver.hpp"


int main() {
	exit(solve("acb..bab.c.*.ab.ba.+.+*a.", 'b', 3) != 7);
}
