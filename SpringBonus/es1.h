#ifndef es1_h
#define es1_h

#include <iostream>
#include <omp.h>
#include <cmath>

#define pi 3.14159

using namespace std;


double es1Static(unsigned dim) {
    double *vec = new double [dim * dim];

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                vec[(i * dim) + j] = 15 * sin(j) * cos(i) * sqrt(2 * i) * pi * pow(j, 6);
            }
        }
    }

    double end = omp_get_wtime();
    delete [] vec;

    return end - start;
}

double es1Dynamic(unsigned dim) {
    double *vec = new double [dim * dim];

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                vec[(i * dim) + j] = 15 * sin(j) * cos(i) * sqrt(2 * i) * pi * pow(j, 6);
            }
        }
    }
    double end = omp_get_wtime();
    delete [] vec;
    return end - start;
}


void es1() {
    cout << "Inserisci dimensione della matrice" << endl;
    unsigned dim;
    cin >> dim;

    cout << "Dimensione della matrice " << dim << " x " << dim << endl;
    cout << "Inserisci numero positivo per scheduling statico, negativo per dinamico" << endl;
    
    double scelta;
    cin >> scelta;

    if (scelta > 0) {
        cout << "Tempo: " << es1Static(dim);
    }
    else if (scelta < 0) {
        cout << "Tempo: " << es1Dynamic(dim);
    }
    else {
        cout << "Non valido!" << endl;
    }
}

#endif