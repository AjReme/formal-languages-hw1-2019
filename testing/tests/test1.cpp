#include "solver.hpp"


int main() {
    return solve("aa.a+a.a.a.", 'a', 3) != 4;
    return solve("aa.a+a.", 'a', 3) != 3;
    return solve("aa.a.aa.a+.", 'a', 4) != 4;
    return solve("aaa.a+.", 'a', 3) != 3;
    return solve("aa.*a.", 'a', 3) != 3;
    return solve("aa.*a.", 'a', 4) != 5;
    return solve("aaa.*.", 'a', 3) != 3;
    return solve("aaa.*.", 'a', 4) != 5;
    return solve("aa*.", 'a', 3) != 3;
    return solve("aa*.", 'a', 4) != 4;
    return solve("a*a.", 'a', 3) != 3;
    return solve("a*a.", 'a', 4) != 4;
    return solve("aa.a.aa.a.a.a.+*", 'a', 15) != 15;
    return solve("aa.a.aa.a.a.a.+*", 'a', 14) != 14;
    return solve("1+a", 'a', 1) != 1;
    return solve("a+1", 'a', 1) != 1;
    return solve("ba.a.ab.b.+*", 'a', 3) != 6;
    return solve("ab+c.aba.*.bac.+.+*b", 'b', 2) != 4;
    return solve("acb..bab.c.*.ab.ba.+.+*a.", 'b', 3) != 7;
}
