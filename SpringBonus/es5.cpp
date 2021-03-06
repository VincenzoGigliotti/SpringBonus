#include "es5.h"


bool** GameOfLife::setta() {
        bool **mat = new bool*[celle];
        #pragma omp parallel for num_threads(nmt)
        for(unsigned long i=0; i < celle; ++i){
            mat[i] = new bool[celle];
            for(int j=0; j < celle; ++j) {
                mat[i][j] = false;
            }
        }
        return mat;
}

void GameOfLife::stampaCelle() {
    for (long int i = 1; i < celle - 1; i++) {
        for (long int j = 1; j < celle - 1; j++) {
            if (attuale[i][j] == true) {
                cout << "1" << " ";
            }
            else {
                cout << "0" << " ";
            }
        }
        cout << endl;
    }
}

void GameOfLife::genera() {
    srand(time(NULL));
    #pragma omp parallel 
    {
        int random;
        #pragma omp for collapse(2) 
        for (long int i = 1; i < celle - 1; i++) {
            for (long int j = 1; j < celle - 1; j++)
            {
                random = rand() % 10 + 1;
                if (random %2 == 0) {
                    attuale[i][j] = true;
                }
                else {
                    attuale[i][j] = false;
                }
            }
        }
    }
}

void GameOfLife::iniziaPartita() {
    cout << "Genero le celle...." << endl;
    genera();
}


unsigned GameOfLife::check(long int i, long int j) {
    unsigned int cont=0;
    #pragma omp parallel for collapse(2) reduction(+ : cont) num_threads(nmt)
        for(int r = i-1; r <= i+1; ++r){
            for(int c = j-1; c <= j+1; ++c){
                if(attuale[r][c])
                    cont++;
            }
        }
        if(attuale[i][j])
            cont--;
        return cont;

}

void GameOfLife::next() {
    bool **nextStep = setta();
    #pragma omp parallel for num_threads(nmt)
    for (long int i = 1; i < celle - 1; i++) {
        for (long int j = 1; j < celle - 1; j++) {
            if (check(i, j) == 3) {
                nextStep[i][j] = true;
            }
            else if (attuale[i][j] == true && check(i, j) == 2) {
                nextStep[i][j] = true;
            }
        }
    }
    #pragma omp parallel for num_threads(nmt)
        for (int i = 0; i < celle; i++) {
            delete [] attuale[i];
        } 
        delete [] attuale;
    attuale = nextStep;
}

long int GameOfLife::celleVive() {
    long int cont = 0;
    #pragma omp parallel for collapse(2) reduction(+ : cont) num_threads(nmt)
    for (int i = 1; i < celle-1; i++) {
        for (int j = 1; j < celle-1; j++) {
            if (attuale[i][j]) {
                cont++;
            }
        }
    }
    return cont;
}

void GameOfLife::startGame() {
    int turn = 1;
    cout << "Inizio del Game Of Life!" << endl;
    cout << "Ogni generazione verranno stampate le celle e indicate quante ancora in vita" << endl << "Il gioco termina quando tutte le celle muoiono" << endl;
    iniziaPartita();
    cout << "Celle generate! Di cui vive: " << celleVive() << endl;
    int cont = 0;
    while (celleVive() > 0) {
        next();
        cout << endl; 
        cout << "Turno n. " << turn << endl;
        cout << endl << "Di cui vive: " << celleVive() << endl;
        cont++;
        if (cont == 10) {
            cout << "Premi 1 per continuare, 2 per interrompere ";
            int scelta;
            cin >> scelta;
            if (scelta == 2) {
                break;
            }
            cont = 0;
        }
        turn++;
    }
}