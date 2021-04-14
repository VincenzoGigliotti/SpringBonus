#include "es1.h"
#include "es2.h"
#include "es3.h"
#include "es4.h"
#include "es5.h"

void runEs5() {
    cout << "Inserire dimensione matrice ";
    int dimensione;
    cin >> dimensione; 
    cout << endl << "Quanti thread usare? ";  
    unsigned nmt; 
    cin >> nmt;     
    GameOfLife *g = new GameOfLife(dimensione, nmt);        
    g->startGame();             
}

void menu() {
    cout << "Vincenzo Gigliotti, springBonus" << endl;
    cout << "Scegli numero esercizio, 0 per uscire" << endl;
    int scelta;
    cin >> scelta;
    while (scelta != 0) {
        switch (scelta) {
        case 1:
            es1();
        break;
        case 2:
            es2();
            break;
        case 3:
            es3();
            break;
        case 4:
            es4();
            break;
        case 5:
            cout << "Inserire dimensione matrice ";
            runEs5();
            break;
        default:
            cout << "Scelta non valida!";
        }
        cout << endl << endl;
        cout << "Scegli numero esercizio, 0 per uscire" << endl;
        cin >> scelta;
    }
}

int main() {
    menu();
   
}