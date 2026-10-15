#include <time.h>
#include <stdio.h>

int fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n; 
    } else {
        return (fibonacci(n - 1) + fibonacci(n - 2));
    }
}

int fibonacci_dynamic(int n, int *DPFib) {
    if (n <= 1) {
        return n;
    } else if (DPFib[n] != -1) {
        return DPFib[n];
    } else {
        DPFib[n] = fibonacci_dynamic(n - 1, DPFib) + fibonacci_dynamic(n - 2, DPFib);
    }
    return DPFib[n];
}

int main() {
    int n = 36;

    int tableau_Fib[n + 1];
    for (int i = 0; i < n + 1; i++) {
        tableau_Fib[i] = -1; 
    }

    clock_t begin1 = clock();
    int res1 = fibonacci(n);
    clock_t end1 = clock();
    double time1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("Naive Fibonacci( %d ) = %d\n en %.6f secondes", n, res1, time1);

    clock_t begin2 = clock();
    int res2 = fibonacci_dynamic(n, tableau_Fib);
    clock_t end2 = clock();
    double time2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Dynamic Fibonacci( %d ) = %d\n en %.6f secondes", n, res2, time2);

    return 0;
}
