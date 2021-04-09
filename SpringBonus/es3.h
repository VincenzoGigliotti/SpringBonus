#ifndef es3_h
#define es3_h

#include <iostream>
#include <omp.h>
#define nt 8
#define ns 1000000000
#define PAD 8
using namespace std;

//rendere le sum dinamiche

void output(double pig, double time) {
    cout << "Time: " << time << endl << "PiGreco: " << pig << endl;
}

void ciclica() {
   int i, nthreads;
    double pig, sum[nt], step = 1.0/(double) ns;
    double start = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel 
    {
        int i, id, n;
        double x;
        id = omp_get_thread_num();
        n = omp_get_num_threads();
        if (id == 0) 
            nthreads = n;
        for (i = id, sum[id] = 0.0; i < ns; i += n) {
            x = (i+0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    double end = omp_get_wtime();
    for (i = 0, pig = 0.0; i < nthreads; i++) {
        pig += sum[i] * step;
    }
    output(pig, end - start);
}

void critica() {
    int i, nthreads;
    double pig, step = 1.0/(double) ns;
    double start = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel 
    {
        int i, id, n;
        double x, sum;
        id = omp_get_thread_num();
        n = omp_get_num_threads();
        if (id == 0) nthreads = n;
        id = omp_get_num_threads();
        for (i = id, sum = 0.0; i < ns; i += nthreads) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical 
            pig += sum * step;
    }
    double end = omp_get_wtime();
    output(pig, end - start);
}

void padding() {
    int i, nthreads;
    double pig, sum[nt][PAD], step = 1.0/(double) ns;
    double start = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel 
    {
        int i, id, n;
        double x;
        id = omp_get_thread_num();
        n = omp_get_num_threads();
        if (id == 0) nthreads = n;
        for (i = id, sum[id][0] = 0.0; i < ns; i += n) {
            x = (i+0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }
    double end = omp_get_wtime();
    for (i = 0, pig = 0.0; i < nthreads; i++) {
        pig += sum[i][0] * step;
    }
   output(pig, end - start);
}

void reduction() {
    double area = 0.0, pig, x;
    int i, n;
    n = 100000;
    
    double start = omp_get_wtime();
    #pragma omp parallel for private(x) reduction(+ : area) 
    for (i = 0; i < n; i++) {
        x = (i + 0.5) /n;
        area += 4.0 / (1.0 + x * x);
    }
    pig = area / n;
    double end = omp_get_wtime();
    
    output(pig, end - start);
}

void monteCarlo() {
    long num_trials = 100000000, i, Ncirc = 0;
    double pig, x, y, r = 1.0;

    double start = omp_get_wtime();
    
    #pragma omp parallel private(x, y) reduction(+ : Ncirc)
    {
        unsigned int seed = (unsigned int) (omp_get_wtime()*10000.0*(double)omp_get_thread_num()/pi);

        #pragma omp for
        for (i = 0; i < num_trials; i++) {
            x = (double) rand_r(&seed) / RAND_MAX;
            y = (double) rand_r(&seed) / RAND_MAX;
            if (((x * x) + (y * y)) <= 1) {
                Ncirc++;
            }
        }
    }
    pig = 4.0 * ((double) Ncirc / (double) num_trials);
    
    double end = omp_get_wtime();
    output(pig, end - start);
}



void es3() {
    monteCarlo();
}




#endif