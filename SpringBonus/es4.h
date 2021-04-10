#ifndef es4_h
#define es4_h
#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

void output(bool find, double time) {
    if (find) {
        cout << "Trovato in: " << time << endl;
        return;
    }
    cout << "Non trovato" << endl;
}

void generate(int *vec, int dimension) {
    srand(time(NULL));

    #pragma omp parallel for
    for (int i = 0; i < dimension; i++) {
        vec[i] = rand() % 1000 + 1;
    }
}

void search(int *vec, int dimension, int numberToSearch) {
    bool find = false;

    if (numberToSearch < 0 || numberToSearch > 1000) {
        cout << "Numero non valido!" << endl;
    }

    double start = omp_get_wtime();

    #pragma omp parallel 
    {
        #pragma omp for 
        for (unsigned long i = 0; i < dimension; i++) {
            #pragma omp cancellation point for
            if (vec[i] == numberToSearch) {
                #pragma omp atomic write
                find = true;
                #pragma omp cancel for
            }
        }
    }

    double end = omp_get_wtime();

    output(find, end - start);
}


void es4() {
    cout << "Inserisci dimensione dell'array" << endl;
    int dimension;
    cin >> dimension;

    int *vec = new int[dimension];
    cout << "Genero con numeri random tra 1 e 1000" << endl;
    generate(vec, dimension);
    
    cout << "Inserisci numero da cercare" << endl;
    int numberToSearch;
    cin >> numberToSearch;
    search(vec, dimension, numberToSearch);

    delete [] vec;
}

#endif