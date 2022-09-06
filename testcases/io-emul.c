/* 
 * This boilerplate code is important for being able to perform I/O.
 * It's just emulated MMIO, with a write to the location magic_rw being
 * turned into a printf in mem.c, and a read from the location magic_rw
 * being turned into a scanf in mem.c.
 * 
 * Always #include this file in your testcase. See gcd.c for an example.
 */

volatile void* magic_rw = (void*) 0xFFFFFFFFFFFFFFFFULL;

void write_int(const int n) {
    *((int *)magic_rw) = n;
}

void write_char(const char c) {
    *((char *)magic_rw) = c;
}

void write_string(const char* s) {
    do {
        char c = *s;
        if (c == 0) return;
        write_char(c);
        s++;
    } while(1);
}

int read_int(void) {
    write_string("Enter int: ");
    return *((int *)magic_rw);
}

char read_char(void) {
    write_string("Enter char: ");
    return *((char *)magic_rw);
}