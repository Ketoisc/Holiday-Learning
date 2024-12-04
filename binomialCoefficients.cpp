// using recurrence relation that nCk = (n-1)C(k-1) + (n-1)Ck
// either the nth value is chosen, or it is not

#define MAXN 50

long int binomial_coefficient(int n, int k) {
    long int bin_co[MAXN + 1][MAXN + 1]; // binomial coefficients table

    for (int i = 0; i <= n; i++) { // initialise values to 1. there is 1 way to choose i items from 0
        bin_co[i][0] = 1;
    }

    for (int j = 0; j <= n; j++) { // initialise values to 1. there is 1 way to choose j items from j
        bin_co[j][j] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) { // fill out the table using the previous elements
            bin_co[i][j] = bin_co[i-1][j-1] + bin_co[i-1][j];
        }
    }
    return bin_co[n][k]; // return the appropriate value
}