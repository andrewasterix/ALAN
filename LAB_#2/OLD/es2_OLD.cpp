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
float fact(float);

Matrice matrixProduct(Matrice);
vector<float> soluzioneSistema(const Matrice &, const Matrice &);

void riduzioneGaussiana(Matrice &, Matrice &);
vector<float> sostituzioneIndietro(Matrice &, Matrice &);

void printVector(const vector<float> &);
void printMatrix(const Matrice &);

int main(int argc, char const *argv[])
{
    /*
        ESERCIZIO 2
    */
    /* Dimensioni matrici fissate */
    const int dimP = 10;

    /* Generazione dimensione della Matrice Tridiagonale */
    int dimT = 10 * (d1 + 1) + d0;

    /*
        Costruzione delle matrici A1, A2, P, T;
    */

    cout << "-------- Esercizio 2 --------\n";

    const Matrice aOne = { {3, 1, -1, 0}, {0, 7, -3, 0}, {0, -3, 9, -2}, {0, 0, 4, -10} };
    const Matrice aTwo = { {2, 4, -2, 0}, {1, 3, 0, 1}, {3, -1, 1, 2}, {0, -1, 2, 1} };
    Matrice P = pascalMatrixGeneration(dimP);
    Matrice T = tridiagonalMatrixGeneration(dimT); 
    cout << "- Matrici A1 A2 P T generate\n";

    /*
        Generazione de termine noto dato dal prodotto b = A · ̄x;
        - Nota: x vettore contentente solo 1, di dimensione pari a quella della matrice; 
    */
    cout << "- Vettori termini noti 𝑏=𝐴∙𝑥̅\n";

    /* Vettore prodotto di dimensione 4 */
    Matrice vectorBaOne = matrixProduct(aOne);
    Matrice vectorBaTwo = matrixProduct(aTwo);

    /* Vettore prodotto di dimensione dimP */
    Matrice vectorBpascal = matrixProduct(P);
    /* Vettore prodotto di dimensione dimT */
    Matrice vectorBtri = matrixProduct(T);

    /* 
        Calcolo delle soluzione dei sistemi
        - Prima viene eseguito l'algoritmo di Riduzione Guassiana
        - In secondo luogo l'algoritmo di Sostituzione all'Indietro
    */
    vector<float> sol_aOne = soluzioneSistema(aOne, vectorBaOne);
    vector<float> sol_aTwo = soluzioneSistema(aTwo, vectorBaTwo);
    vector<float> sol_P = soluzioneSistema(P, vectorBpascal);
    vector<float> sol_T= soluzioneSistema(T, vectorBtri);

    cout << "Risultato del sistema A1x = B: ";
    printVector(sol_aOne);
    cout  << endl;

    cout << "Risultato del sistema A2x = B: ";
    printVector(sol_aTwo);
    cout << endl;

    cout << "Risultato del sistema Px = B: "; 
    printVector(sol_P);
    cout << endl;
    cout << "Risultato del sistema Tx = B: ";
    printVector(sol_T);
    cout << endl;
    
    return 0;
}

/* Genera la matrice di Pascal - si veda es1 */
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

/* Genera la matrice Tridiagonale - si veda es1 */
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

/* Esegue il prodotto tra la Matrice m e il vettore x, 
    il risultato è il termine noto del sistema */
Matrice matrixProduct(Matrice m){

    Matrice vectorB(m.at(0).size(), vector<float>(1));

    for (int i = 0; i < m.size(); i++){
		float sum = 0;
		for (int j = 0; j < m.at(0).size(); j++){
			sum += m.at(i).at(j);
		}
		vectorB.at(i).at(0) = sum;
	}
    return vectorB;
}

/* Algoritmo di Riduzione Gaussiana per il Sistema generalizzato Ax=b */
void riduzioneGaussiana(Matrice &coefficienti, Matrice &termineNoto){
    
    for (int k = 0; k < coefficienti.at(0).size() - 1; k++) {
		for (int i = k+1; i < coefficienti.size(); i++){

            /* Calcolo del coefficiente m(i,k) risulatante da a(i,k)/a(k,k) */
			float m = (coefficienti.at(i).at(k)) / (coefficienti.at(k).at(k));
            /* Calcolo diretto del termine noto corispondente alla riga presa in esame */
			termineNoto.at(i).at(0) -= m * termineNoto.at(k).at(0);
			
            /* Calcolo di tutti i nuovi elementi nella riga presa in esame */
			for (int j = k+1; j < coefficienti.at(0).size(); j++)
				coefficienti.at(i).at(j) -= m*coefficienti.at(k).at(j);
			
            /* Pongo il primo elemento della riga della sotto matrice pari a 0 per definizione -> a(i,k) - a(i,k)*/
            coefficienti.at(i).at(k) = 0;
		}
	}
}
/* Algoritmo di Sostituzione all'indietro per il Sistema generalizzato Ax=b*/
vector<float> sostituzioneIndietro(Matrice &coefficienti, Matrice& termineNoto){

    /* Vettore soluzione */
    vector<float> soluzione(coefficienti.at(0).size());
    /* Counter di tracciamento esecuzione */
    int counter = 0;

    /* Calcolo del primo risultato utile, ovvero calcolo il risultato della x sull'ultima riga della matrice ridotta */
    soluzione.at(soluzione.size() - 1) = (termineNoto.at(termineNoto.size() - 1).at(0)) / (coefficienti.at(coefficienti.size()-1).at(coefficienti.size()-1));
    counter++;

    /* Procedo iterativamente all'indietro, salendo di riga in riga nella matrice partendo dalla penultima riga della matrice */
    for(int i = coefficienti.size() - 2; i >= 0; i--){
        float sub = 0;
        /* Sommo tutti le x(j) della riga inferiore analizzata prima moltiplicate per il loro coefficiente -> ∑[a(k,j)*x(j)]*/
        for(int j = 1; j <= counter; j++)
            sub += soluzione.at(soluzione.size()-j) * coefficienti.at(i).at(coefficienti.size()-j);
        /* Eseguo la formula di risoluzione x(i) = {b(j) - ∑[a(k,j)*x(j)]] / a(i,i)} */
        soluzione.at(i) = (termineNoto.at(i).at(0) - sub) / coefficienti.at(i).at(i);
        counter++;
    }
 
    return soluzione;
}
/* Soluzione del sistema */
vector<float> soluzioneSistema(const Matrice &a, const Matrice &b){
    Matrice coefficienti = a;
    Matrice termineNoto = b;
    
    riduzioneGaussiana(coefficienti, termineNoto);
    return sostituzioneIndietro(coefficienti, termineNoto);
}

/* Fattoriale */
float fact(float number){
    if(number == 1 || number <= 0) return 1;
    return number * fact(number - 1);
}

/* Stampa Vettore */
void printVector(const vector<float> &v){
	for (int i = 0; i<v.size(); i++)
		cout << v.at(i) << " ";
	cout << endl;
}

/* Stampa Matrice */
void printMatrix(const Matrice &m){
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(i).size(); j++)
			cout << m.at(i).at(j) << " ";
		cout << endl;
	}
}