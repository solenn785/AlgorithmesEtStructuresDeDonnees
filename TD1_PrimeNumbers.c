#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool est_premier(int n) {
    if (n < 2) return false;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            return false;
        }
        i++;
    }
    return true;
}

int nombres_premiers_naif(int n) {
    int compteur = 0;
    for (int i = 2; i < n; i++) {
        if (est_premier(i)) { 
            compteur++;
        }
    }
    return compteur;
}

int nombres_premiers_efficient(int n) {
    if (n <= 2) return 0;

    bool *is_prime = malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p < n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i < n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    int compteur = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            compteur++;
        }
    }

    free(is_prime);
    return compteur;
}

int main() {
    int n = 10000; 

    clock_t begin1 = clock();
    int res1 = nombres_premiers_naif(n);
    clock_t end1 = clock();
    double time1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;

    printf("Naive: Il y a %d nombres premiers < %d\n en %.6f secondes\n", res1, n, time1);
    clock_t begin2 = clock();
    int res2 = nombres_premiers_efficient(n);
    clock_t end2 = clock();
    double time2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("Efficace: Il y a %d nombres premiers < %d en %.6f secondes\n", res2, n, time2);
    return 0;
}
