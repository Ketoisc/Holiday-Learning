using namespace std;

long int fibonacci(int n) {
    long int lastValue1 = 1; // first two values of fibonacci sequence are 0 and 1
    long int lastValue2 = 0;
    long sum; // placeholder for the sum

    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    if (n == 2) {
        return 1;
    }

    for (int i = 2; i < n; i++) { // starts from the start and adds each previous fibonacci number. 
    // maintains three variables to hold the sums and change them through each loop to maintain the previous 2 fib numbers
        sum = lastValue1 + lastValue2;
        lastValue2 = lastValue1;
        lastValue1 = sum;
    }
    return (lastValue1 + lastValue2);
}