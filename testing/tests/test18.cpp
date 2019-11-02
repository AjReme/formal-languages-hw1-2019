#include "solver.hpp"


int main() {
	return solve("ab+c.aba.*.bac.+.+*b", 'b', 2) != 4;
}
