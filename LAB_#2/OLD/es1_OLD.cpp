#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

/* Numero di matricola: Andrea Franceschetti 4357070 -> d0 = 0; d1 = 7*/
const int d0 = 0;
const int d1 = 7;

typedef vector<vector<float>> Matrice;

Matrice pascalMatrixGeneration(int);
Matrice tridiagonalMatrixGeneration(int);
float normaInfinito(const Matrice &);
float fact(float);

void printMatrix(Matrice);

int main(int argc, char const *argv[])
{
    /* Dimensioni matrici fissate */
    const int dimP = 10;

    /* Generazione dimensione della Matrice Tridiagonale */
    int dimT = 10 * (d1 + 1) + d0;

    /*
        ESERCIZIO 1 - A: Norma INFINITO DELLE MATRICI
    */

    cout << "-------- Esercizio 1 - A --------\n";

    Matrice aOne = { {3, 1, -1, 0}, {0, 7, -3, 0}, {0, -3, 9, -2}, {0, 0, 4, -10} };

    Matrice aTwo = { {2, 4, -2, 0}, {1, 3, 0, 1}, {3, -1, 1, 2}, {0, -1, 2, 1} };

    printMatrix(aOne);
    cout << " - La norma della prima Matrice A e': " << normaInfinito(aOne) << endl;

    printMatrix(aTwo);
    cout << " - La norma della seconda Matrice A e': " << normaInfinito(aTwo) << endl;

    /*
        ESERCIZIO 1 - B: Matrice Pascal "P"
    */
    cout << "-------- Esercizio 1 - B --------\n";
    
    Matrice P = pascalMatrixGeneration(dimP);

    cout << " - Matrice di Pascal 'P' generata \n";
    printMatrix(P);
    cout << " - La norma della Matrice di PASCAL P e': " << normaInfinito(P) << endl;

    /*
        ESERCIZIO 1 - C: Matrice Tridiagonale T dove
            - i = j => T[i][j] = 2 
            - |i - j| => T[i][j] = -1
            - altrimenti T[i][j] = 0
    */
    cout << "-------- Esercizio 1 - C --------\n";
    
    Matrice T = tridiagonalMatrixGeneration(dimT); 

    cout << " - Matrice di Tridiagonale 'T' generata \n";
    printMatrix(T);
    cout << " - La norma della Matrice di TRIDIAGONALE T e': " << normaInfinito(T) << endl;

    return 0;
}

Matrice pascalMatrixGeneration(int dimP){
	Matrice P(dimP);

    for(int i = 0; i < dimP; i++)
        P.at(i).resize(dimP);

    for (int i = 1; i <= dimP; i++){
        for (int j = 1; j <= dimP; j++){

            float numeratore = fact(i + j - 2);
            float denominatore = fact(i - 1) * fact(j - 1);
            P.at(i - 1).at(j - 1) = numeratore / denominatore;
        }
    }
    return P;
}

Matrice tridiagonalMatrixGeneration(int dimT){
	Matrice T(dimT);

    for(int i = 0; i < dimT; i++)
        T.at(i).resize(dimT);

    for(int i = 0; i < dimT; i++){
        for(int j = 0; j < dimT; j++){
            if(i == j) T.at(i).at(j) = 2;
            else if(abs(i - j) == 1) T.at(i).at(j) = -1;
            else T.at(i).at(j) = 0;
        }
    }
    return T;
}

float normaInfinito(const Matrice &m){

    float max = 0.0;

    for (int i = 0; i < m.size(); ++i) {
        float sum = 0.0;
        
        for (int j = 0; j < m.at(i).size(); ++j)
            sum += fabs(m.at(i).at(j));
        
        if (sum > max) max = sum;
    }

    return max;
}

float fact(float number){
    if(number == 1 || number <= 0) return 1;
    return number * fact(number - 1);
}

void printMatrix(Matrice m){
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(i).size(); j++)
			cout << m.at(i).at(j) << " ";
		cout << endl;
	}
}