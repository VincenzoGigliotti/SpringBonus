#ifndef es2_h
#define es2_h
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <climits>
#define dim 100000000
using namespace std;

void generate(int *a) {
    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        a[i] = rand()%10 + 1;
    }
}

double sum(int *a, int *b, int *c) {
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < dim; i++) {
            c[i] = a[i] + b[i];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

double findmax(int *c) {
    int max = INT_MIN;

    double start = omp_get_wtime();
    
    #pragma omp parallel for
    for (int i = 0; i < dim; i++) {
        if (c[i] > max) {
            max = c[i];
        }
    }
    double end = omp_get_wtime();
    
    cout << "Il massimo è: " << max << endl;
    
    return end - start;
}

void es2() {
    int *a = new int[dim];
    int *b = new int[dim];
    int *c = new int[dim];

    generate(a);
    generate(b);

    cout << "Tempo per calcolare c: " << sum(a, b, c) << endl;

    cout << "Tempo per trovare il massimo in c: " << findmax(c) << endl;


    delete [] a;
    delete [] b;
    delete [] c;
}


#endif