#ifndef ES5_H
#define ES5_H
#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

class GameOfLife {
    private:
    bool **attuale;
    long int celle;
    void genera();

    public:
    GameOfLife(long celle) {
        this->celle = celle;
        attuale = setta();
    }

    ~GameOfLife() {
        #pragma omp parallel for
        for (int i = 0; i < celle; i++) {
            delete [] attuale[i];
        } 
        delete [] attuale;
    }
       
    void iniziaPartita();
    void stampaCelle();
    void next();
    unsigned check(long int i, long int j);
    bool** setta();



};


#endif