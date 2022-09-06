
void* magic = (void*) 0xFFFFFFFFFFFFFFFFULL;

void write_int(const int n) {
    *((int *)magic) = n;
}

void start() {
    write_int(-42);
    write_int(50000);
}