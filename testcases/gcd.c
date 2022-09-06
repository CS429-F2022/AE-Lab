#include "io-emul.c"

int gcd(int u, int v) {
    if (u == v) return u;
    if (1 == u) return u;
    if (u > v) {u ^= v ^= u ^= v;}  // Exchange u and v if needed to ensure that u < v in what follows.
    return gcd(u, v-u);
}    

/* 
 * This is where program execution will start.
 * It is the logical equivalent of main() in a 
 * "conforming freestanding implementation". 
 * See Sections 4 and 5.1.2.1 in the C99 standard.
 * 
 * There is nothing special about the name "start", but the
 * name you choose for this routine has to be identified as
 * the entry point using the -e command-line option in gcc.
 */

void start() {
    write_string("gcd(10, 25) = "); write_int(gcd(10, 25));
    write_string("gcd(21, 14) = "); write_int(gcd(21, 14));
    write_string("gcd(79, 83) = "); write_int(gcd(79, 83));
}
