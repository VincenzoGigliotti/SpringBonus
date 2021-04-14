#ifndef es2_h
#define es2_h
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <climits>
#define dim 100000000
using namespace std;


void output(int max, double time) {
     cout << "Il massimo è: " << max << endl;
     cout << "Tempo per trovare il massimo: " << time << endl;
}

void generate(int *a) {
    cout << "Genero la matrice..." << endl;
    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        a[i] = rand()%10 + 1;
    }
}

double sum(int *a, int *b, int *c, unsigned nmt) {
    double start = omp_get_wtime();

    #pragma omp parallel num_threads(nmt)
    {
        #pragma omp for
        for (int i = 0; i < dim; i++) {
            c[i] = a[i] + b[i];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

double findmax(int *c, unsigned nmt) {
    int currentmax = INT_MIN;

    double start = omp_get_wtime();
    
    #pragma omp parallel for reduction(max : currentmax) num_threads(nmt)
    for (int i = 0; i < dim; i++) {
        if (c[i] > currentmax) {
            currentmax = c[i];
        }
    }
    double end = omp_get_wtime();
     
    return end - start;
    output(currentmax, end - start);
}

void es2() {
    int *a = new int[dim];
    int *b = new int[dim];
    int *c = new int[dim];
    cout << "Inserisci numero threads" << endl;
    unsigned nmt;
    cin >> nmt;
    generate(a);
    generate(b);

    cout << endl << "Tempo per calcolare c: " << sum(a, b, c, nmt) << endl;

    findmax(c, nmt);

    delete [] a;
    delete [] b;
    delete [] c;
}


#endif