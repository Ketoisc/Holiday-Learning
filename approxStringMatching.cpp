#define MATCH 0
#define INSERT 1
#define DELETE 2

#define MAXLEN 50

int string_compare_r(char* string, char* target, int m[MAXLEN+1][MAXLEN+1]) {
    int optionCost[3];
    for (int i = 0; i <= MAXLEN; i++) {
        row_init(i, m);
    }

    if (i == 0) {
        return (j*insDelCost(' ');)
    }
}