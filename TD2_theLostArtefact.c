#include "structuresDeDonnees.h"
#include "stdio.h"
#include <math.h>
#include <time.h>

//compilation: gcc theLostArtefact.c structuresDeDonnees.c -o tla &&  ./tla

// Preparing the sorting system
int is_sorted_increasing(Array A){
    int n = array_length(A);
    for(int i=0; i<n-1;i=i+1){
        int a = array_get(A,i);
        int b = array_get(A,i+1);
        if(a>b){
            return 0;}
    }
    return 1;

}

// Linear search
int linearSearch(Array A,int x ){
    int n = array_length(A);
    for(int i=0; i<= n; i=i+1){
        int a = array_get(A,i);
        if(a==x){return i;}
    }
    return -1;
}

// Jump search
int jumpSearch(Array A, int x){
    if (is_sorted_increasing(A) == 0) {
        return -1;
    }
    int n = array_length(A);
    int jumpSize = (int)sqrt(n);
    int prev = 0;
    int m = jumpSize;  
    while (prev < n) {
        int limit = m;
        if (n < m) {
            limit = n;
        }       
        if (array_get(A, limit-1)>=x) {
            break;
        }      
        prev = m;
        m = m + jumpSize;
        if (prev >= n) {
            return -1;
        }
    }  
    int fin = m;
    if (n < m) {
        fin = n;
    }
   
    
    for (int i = prev; i < fin; i = i + 1){
        if (array_get(A, i) == x){
            return i;
        }
    }
    return -1;   
}

// Binary search
int binarySearch(Array A, int x){
    if(is_sorted_increasing(A)==0){return -1;}
    int n = array_length(A);
    int low = 0;
    int high = n-1;
    int mid = 0;
    int aMid = 0;
    while(low<=high){
        mid = (low+high)/2;
        aMid = array_get(A, mid);
        if (aMid ==x){return mid;}
        if (aMid < x){low = mid+1;}
        else{high = mid-1;}
    }
    return -1;
}


// Tests
int main(){
    Array A = newArray();array_append(A, 1);array_append(A, 2);array_append(A, 3);array_append(A, 4);array_append(A, 5);
    printf("Le tableau augmente strictement %i\n",is_sorted_increasing(A));
    printf("L'index trouvé avec LinearSearch est %i\n",linearSearch(A,3));
    array_print(A);
    linearSearch(A, 3);
    printf("L'index trouvé avec jumpSearch est %i\n",jumpSearch(A,3));
    printf("L'index trouvé avec binarySearch est %i\n",binarySearch(A,3));
    Array bigArray = newArray();
        for (int i = 0; i < 10000; i=i+1) {
            array_append(bigArray, i * 2); 
        }
    // Performance comparaison
    clock_t begin1 = clock();
    printf("L'index trouvé avec LinearSearch est %i ",linearSearch(bigArray,3));
    clock_t end1 = clock();
    double time1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time1);

    clock_t begin2 = clock();
    printf("L'index trouvé avec jumpSearch est %i ",jumpSearch(bigArray,3));
    clock_t end2 = clock();
    double time2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time2);

    clock_t begin3 = clock();
    printf("L'index trouvé avec binarySearch est %i ",jumpSearch(bigArray,3));
    clock_t end3 = clock();
    double time3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("en %.6f secondes\n", time3);
}
