
char* magic = (char*) 0xFFFFFFFFFFFFFFFFULL;

void write_char(const char c) {
    *magic = c;
}

void write_string(const char* s) {
    do {
        char c = *s;
        if (c == 0) return;
        write_char(c);
        s++;
    } while(1);
}

int strcmp(void *vs, void *vt) {
    int i;
    char *s = (char *) vs;
    char *t = (char *) vt;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0') return 0;
    return s[i] - t[i];
}

void swap(void *v[], int i, int j) {
    void *temp = v[i]; v[i] = v[j]; v[j] = temp;
}

void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

char *months[12] = 
    {"January\n", "February\n", "March\n",
     "April\n", "May\n", "June\n",
     "July\n", "August\n", "September\n",
     "October\n", "November\n", "December\n"};

void start() {
    qsort((void *) months, 0, 11, strcmp);
    for (int i = 0; i < 11; i++)
        write_string(months[i]);
}
