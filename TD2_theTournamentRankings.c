#include "structuresDeDonnees.h"
#include "stdio.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

//compilation : gcc theTournamentRankings.c structuresDeDonnees.c -o ttr && ./ttr


// Preparing the sorting system
void swap_int(int *a, int *b) { 
    int c = *a; 
    *a = *b; 
    *b = c; 
} 
void array_swap(Array A, int i, int j) {
    int temp = array_get(A, i);
    array_set(A, i, array_get(A, j));
    array_set(A, j, temp);
}

int is_sorted_ascending(Array A){
    int n = array_length(A);
    for(int i=0; i<n-1;i=i+1){
        int a = array_get(A,i);
        int b = array_get(A,i+1);
        if(a>b){
            return 0;}
    }
    return 1;

}

Array copy_array(Array A){
    Array B = newArray();
    int content = 0;
    int n = array_length(A);
    for(int i=0; i<n;i= i+1){
        content = array_get(A,i);
        array_append(B,content);
    }
    return B;
}

// Selection sort

Array selectionSort(Array A) {
    int n = array_length(A);
    for (int i = 0; i<=n-2; i =i+1) {
        int min = i;
        for (int j = i+1; j <= n-1; j = j+1) {
            if (array_get(A, j)<array_get(A, min)){
                min = j;
            }
        }
        array_swap(A, i, min);
    }
    return A;
}

//insertion sort
Array insertionSort(Array A) {
    int n = array_length(A);
    for (int i=1;i<n;i=i+1) {
        int key = array_get(A, i);
        int j = i-1;
        while (j >= 0 && array_get(A, j)>key) {
            array_set(A, j+1, array_get(A, j));
            j = j-1;
        }
        array_set(A, j+1, key);
    }
    return A;
}

//bubble sort
Array bubbleSort(Array A){
    int n = array_length(A);
    int swapped;
    int key1;
    int key2;
    for (int i=0; i<n-1;i=i+1){
        swapped = 0;
        for (int j=0; j<n-i-1; j=j+1) {
            key1 = array_get(A, j);
            key2 = array_get(A, j + 1);
            if (key1 > key2) {
                swap_int(&key1, &key2);
                array_set(A, j, key1);
                array_set(A, j + 1, key2);
                swapped = 1;
            }
        }
        if (swapped == 0){
            break;
        }
    }
    return A;
}

//merge sort 
Array merge(Array L, Array R) {
    Array merged = newArray();
    int i = 0;
    int j = 0;
    int nL = array_length(L);
    int nR = array_length(R);

    while (i < nL && j < nR) {
        if (array_get(L, i) <= array_get(R, j)) {
            array_append(merged, array_get(L, i));
            i = i+1;
        } 
        else {
            array_append(merged, array_get(R, j));
            j=j+1;
        }
    }

    while (i < nL) {
        array_append(merged, array_get(L, i));
        i=i+1;
    }

    while (j < nR) {
        array_append(merged, array_get(R, j));
        j=j+1;
    }
    return merged;
}



Array mergeSort(Array A){
    int n = array_length(A);
    int mid;
    Array L = newArray();
    Array R = newArray();
    if(n<=1){return A;}
    mid = n / 2;
    for (int i = 0;i<mid;i=i+1) {
        array_append(L, array_get(A, i));
    }
    for (int i = mid;i<n;i=i+1) {
        array_append(R, array_get(A, i));
    }
    L = mergeSort(L);
    R = mergeSort(R);
    return merge(L, R);
}

//quick sort
int partition(Array A, int low, int high) {
    int pivot = array_get(A, high);
    int i = (low-1);

    for (int j =low; j<=high-1;j=j+1) {
        if (array_get(A, j) < pivot) {
            i=i+1;
            array_swap(A,i,j);
        }
    }
    array_swap(A, i+1,high);
    return (i+1);
}


Array quickSort(Array A, int low, int high){
    int p;
    if (low<high){
        p = partition(A,low,high);
        quickSort(A,low,p-1);
        quickSort(A,p+1, high);
    }
        return A;
}

int main() { 
    //tests
    int a = 5; int b = 7;swap_int(&a, &b); 
    printf("a=%i, b=%i \n", a, b);
    Array A = newArray();array_append(A, 1);array_append(A, 2);array_append(A, 3);array_append(A, 4);array_append(A, 5);
    printf("Le tableau est dans l'ordre croissant: %i\n", is_sorted_ascending(A));
    printf("Le tableau qui contient le contenu recopié de A est: ");
    array_print(copy_array(A));

    Array notSortedArray = newArray();array_append(notSortedArray, 3);array_append(notSortedArray, 2);array_append(notSortedArray, 1);array_append(notSortedArray, 4);array_append(notSortedArray, -3);
    printf("Le tableau trié aevc selectionSort est:");
    array_print(selectionSort(notSortedArray));

    printf("Le tableau trié avec insertionSort est:");
    array_print(insertionSort(notSortedArray));

    printf("Le tableau trié avec bubbleSort est:");
    array_print(bubbleSort(notSortedArray));

    printf("Le tableau trié avec mergeSort est:");
    array_print(mergeSort(notSortedArray));
    
    printf("Le tableau trié avec quickSort est:");
    int n = array_length(notSortedArray);
    array_print(quickSort(notSortedArray, 0, n-1));


    Array bigArray = newArray();
    for (int i = 0; i < 500; i = i + 1) {
        int randomNum = rand() % 101; 
        array_append(bigArray, randomNum);
    }
    // Performance comparaison
    Array nonSortedBigArray = copy_array(bigArray);
    clock_t begin1 = clock();
    printf("Le tableau est trié avec selectionSort ");
    selectionSort(nonSortedBigArray);
    clock_t end1 = clock();
    double time1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time1);

    clock_t begin2 = clock();
    nonSortedBigArray = copy_array(bigArray);
    printf("Le tableau est trié avec insertionSort ");
    insertionSort(nonSortedBigArray);
    clock_t end2 = clock();
    double time2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time2);

    clock_t begin3 = clock();
    nonSortedBigArray = copy_array(bigArray);
    printf("Le tableau est trié avec bubbleSort ");
    bubbleSort(nonSortedBigArray);
    clock_t end3 = clock();
    double time3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time3);

    clock_t begin4 = clock();
    nonSortedBigArray = copy_array(bigArray);
    printf("Le tableau est trié avec mergeSort ");
    mergeSort(nonSortedBigArray);
    clock_t end4 = clock();
    double time4 = (double)(end4 - begin4) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time4);

    clock_t begin5 = clock();
    nonSortedBigArray = copy_array(bigArray);
    printf("Le tableau est trié avec quickSort ");
    int l = array_length(nonSortedBigArray);
    quickSort(nonSortedBigArray, 0, l-1);
    clock_t end5 = clock();
    double time5 = (double)(end5 - begin5) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time5);
}


