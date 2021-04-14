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
    unsigned nmt;
    void genera();
    void iniziaPartita();
    void stampaCelle();
    void next();
    unsigned check(long int i, long int j);
    bool** setta();
    long int celleVive();

    public:
    GameOfLife(long celle, unsigned nmt) {
        this->celle = celle;
        this->nmt = nmt;
        attuale = setta();
    }

    ~GameOfLife() {
        #pragma omp parallel for
        for (int i = 0; i < celle; i++) {
            delete [] attuale[i];
        } 
        delete [] attuale;
    }
    
    void startGame();
   


};


#endif