
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

void test_switch(const int day) {
    switch (day) {
    case 1:     write_string("Sunday\n"); break;
    case 2:     write_string("Monday\n"); break;
    case 3:     write_string("Tuesday\n"); break;
    case 4:     write_string("Wednesday\n"); break;
    case 5:     write_string("Thursday\n"); break;
    case 6:     write_string("Friday\n"); break;
    case 7:     write_string("Saturday\n"); break;
    default:    write_string("Invalid input\n"); break;
    }
}

void start() {
    for (int i = 0; i < 8; i++) test_switch(i);
}
