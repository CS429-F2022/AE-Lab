
char* magic = (char*) 0xFFFFFFFFFFFFFFFFULL;

const int vec[32] = {0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
 8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31};

void write_int(const int n) {
    *magic = n;
}

int vecadd(const int* v, const int n) {
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        sum += v[i];
        sum -= v[i+1];
    }
    return sum;
}    

void start() {
    int sum = vecadd(vec, 32);
    write_int(sum);
}
