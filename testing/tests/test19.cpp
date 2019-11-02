#include "solver.hpp"


int main() {
	return solve("acb..bab.c.*.ab.ba.+.+*a.b3", 'b', 3) != 7;
}
