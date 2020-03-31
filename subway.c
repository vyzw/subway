#include <stdio.h>
typedef signed char byte;

int sub(int x, int y) {
    // returns the difference between x and y
    return x - y;
}

int neg(int z) {
    // returns the additive inverse of z
    return sub(0, z);
}

int add(int x, int y) {
    // returns the sum of x and y
    return sub(x, neg(y));
}

int not(int z) {
    // returns the logical negation of the boolean z
    return sub(1, z);
}

int id(int z) {
    // returns z
    return z;
}

int id2(int x, int y) {
    // returns x
    return x;
}

int x2en(int z, int n) {
    // returns the product between z and the nth power of 2, given that 0 <= n <= 256
    static int (*const recurse[3])(int, int) = { id2, x2en, add };
    n = sub(n, 1);
    int b = add(((byte*) &n)[1], 1);
    return recurse[b](recurse[add(b, b)](z, z), n);
}

int end() {
    // returns 0 if little-endian, 1 if big-endian
    int i = 1;
    return not(*((byte*) &i));
}

int bit(int z, int e, int m, int n) {
    // given endianness e, returns the nth bit of the mth byte of z
    static int (*const toggle[2])(int) = { id, neg };
    int b = (byte) x2en(((byte*) &(&z)[e])[toggle[e](add(m, e))], sub(7, n));
    return neg(((byte*) &b)[1]);
}

int lt0(int z) { 
    // returns 1 if z < 0, otherwise returns 0
    return bit(z, not(end()), 0, 7);
}

int or(int x, int y) {
    // returns the logical disjunction of booleans x and y
    int sum = add(x, y);
    int e = end();
    return add(bit(sum, e, 0, 0), bit(sum, e, 0, 1));
}

int and(int x, int y) {
    // returns the logical conjunction of booleans x and y
    return sub(add(x, y), or(x, y));
}

int eq0(int z) {
    // returns 1 if z == 0, otherwise 0
    return not(or(lt0(z), lt0(neg(z))));
}

int eq(int x, int y) {
    // returns 1 if x == y, otherwise 0
    return eq0(sub(x, y));
}

int tern(int b, int x, int y) {
    // returns x if b, otherwise y
    int toggle[2] = { y, x };
    return toggle[b];
}

int lt(int x, int y) {
    // returns 1 if x < y, otherwise 0
    int b = lt0(x);
    return tern(eq(b, lt0(y)), lt0(sub(x, y)), b);
}

int main(void) {
    return 0;
}