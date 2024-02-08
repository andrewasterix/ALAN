#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

/* Numero di matricola: Andrea Franceschetti 4357070 -> d0 = 0; d1 = 7*/
const int d0 = 0;
const int d1 = 7;

typedef vector<vector<float>> Matrice;

/* Funzioni per Esercizio 1 */
Matrice pascalMatrixGeneration(int);
Matrice tridiagonalMatrixGeneration(int);
float normaInfinito(const Matrice &);
float fact(float);

/* Funzioni per Esercizio 2 */
Matrice matrixProduct(Matrice);
vector<float> soluzioneSistema(const Matrice &, const Matrice &);
void pivotingParziale(Matrice &, Matrice &, int);
void riduzioneGaussiana(Matrice &, Matrice &);
vector<float> sostituzioneIndietro(Matrice &, Matrice &);

/* Funzioni per Esercizio 3 */
Matrice matricePerturbazione(const int);
Matrice prodottoScalare(const Matrice &, int);
Matrice perturbazioneTermineNoto(const Matrice &, const Matrice &);

/* Funzioni Generiche */
void printVector(const vector<float> &);
void printMatrix(const Matrice &);

int main(int argc, char const *argv[])
{
    /* Dimensioni matrici fissate */
    const int dimA = 4;
    const int dimP = 10;

    /* Generazione dimensione della Matrice Tridiagonale */
    int dimT = 10 * (d1 + 1) + d0;


    /* ESERCIZIO N. 1 */
    const Matrice aOne = { {3, 1, -1, 0}, {0, 7, -3, 0}, {0, -3, 9, -2}, {0, 0, 4, -10} };
    const Matrice aTwo = { {2, 4, -2, 0}, {1, 3, 0, 1}, {3, -1, 1, 2}, {0, -1, 2, 1} };
    
    cout << " - La norma della prima Matrice A e': " << normaInfinito(aOne) << endl;
    cout << " - La norma della seconda Matrice A e': " << normaInfinito(aTwo) << endl;

    Matrice P = pascalMatrixGeneration(dimP);
    cout << " - Matrice di Pascal 'P' generata \n";
    printMatrix(P);
    cout << " - La norma della Matrice di PASCAL P e': " << normaInfinito(P) << endl;

    Matrice T = tridiagonalMatrixGeneration(dimT); 
    cout << " - Matrice di Tridiagonale 'T' generata \n";
    printMatrix(T);
    cout << " - La norma della Matrice di TRIDIAGONALE T e': " << normaInfinito(T) << endl;

    cout << endl;

    /*
        ESERCIZIO N. 2
    */
    cout << "-------- Esercizio 2 --------\n";

    /*
        Generazione de termine noto dato dal prodotto b = A · ̄x;
        - Nota: x vettore contentente solo 1, di dimensione pari a quella della matrice; 
    */
    cout << " - Calcolo vettori termini noti 𝑏=𝐴∙𝑥̅\n";

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

    cout << " - Risultato del sistema A1x = B: ";
    printVector(sol_aOne);
    cout  << endl;

    cout << " - Risultato del sistema A2x = B: ";
    printVector(sol_aTwo);
    cout << endl;

    cout << " - Risultato del sistema Px = B: "; 
    printVector(sol_P);
    cout << endl;
    cout << " - Risultato del sistema Tx = B: ";
    printVector(sol_T);
    cout << endl;

    /*
        ESERCIZIO N. 3
    */
    cout << "-------- Esercizio 3 --------\n";

    /* Risoluzione per aOne */
    Matrice vectorδb_aOne = prodottoScalare(matricePerturbazione(dimA), normaInfinito(vectorBaOne));
    vectorBaOne = perturbazioneTermineNoto(vectorBaOne, vectorδb_aOne);
    sol_aOne = soluzioneSistema(aOne, vectorBaOne);
    
    /* Risoluzione per aTwo */
    Matrice vectorδb_aTwo = prodottoScalare(matricePerturbazione(dimA), normaInfinito(vectorBaTwo));
    vectorBaTwo = perturbazioneTermineNoto(vectorBaTwo, vectorδb_aTwo);
    sol_aTwo = soluzioneSistema(aTwo, vectorBaTwo);
    
    /* Risoluzione per P */
    Matrice vectorδb_pascal = prodottoScalare(matricePerturbazione(dimP), normaInfinito(vectorBpascal));
    vectorBpascal = perturbazioneTermineNoto(vectorBpascal, vectorδb_pascal);
    sol_P = soluzioneSistema(P, vectorBpascal);

    /* Risoluzione per T */
    Matrice vectorδb_tri = prodottoScalare(matricePerturbazione(dimT), normaInfinito(vectorBtri));
    vectorBtri = perturbazioneTermineNoto(vectorBtri, vectorδb_tri);
    sol_T = soluzioneSistema(T, vectorBtri);
    
    cout << "Risultato del sistema A1x = (B + δB): ";
    printVector(sol_aOne);
    cout  << endl;

    cout << "Risultato del sistema A2x = (B + δB): ";
    printVector(sol_aTwo);
    cout << endl;

    cout << "Risultato del sistema Px = (B + δB): "; 
    printVector(sol_P);
    cout << endl;

    cout << "Risultato del sistema Tx = (B + δB): ";
    printVector(sol_T);
    cout << endl;

    return 0;
}

/*
    ESERCIZIO 1
*/

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

/* Calcolo della NormaInfinito per la matrice data */
float normaInfinito(const Matrice &m){

    float max = 0.0;

    for (int i = 0; i < m.size(); ++i) {
        float sum = 0.0;
        
        /* Sommo tutti i valori della riga i della matrice */
        for (int j = 0; j < m.at(i).size(); ++j)
            sum += fabs(m.at(i).at(j));
        
        /* Se la somma precedente è maggiore del max fissato, 
            essa diventa il nuovo valore di norma */
        if (sum > max) max = sum;
    }

    return max;
}

/* Fattoriale */
float fact(float number){
    if(number == 1 || number <= 0) return 1;
    return number * fact(number - 1);
}

/*
    ESERCIZIO 2
*/

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

/* Pivoting Parziale della matrice, ricerca di una riga con pivot in posizione k 
    maggiore di quello di partenza */
void pivotingParziale(Matrice &m, Matrice &b, int k){

    /* Il max è il primo elemento della riga */
    float max = fabs(m.at(k).at(k));
    int row = k;

    /* Analisi sugli elementi della colonna k*/
    for(int i = k+1; i < m.size(); i++){
        /* Trovato un elemento più grande del max in analisi, 
            estraggo la riga per eseguire successivamente lo scambio di righe
            sostituisco il valore trovato con il max che ho in analisi, 
            perchè il nuovo valore sarà sempre più grande del primo in analisi */
        if(fabs(m.at(i).at(k)) > max){
            max = fabs(m.at(i).at(k));
            row = i;    
        }

    }

    /* Se ho trovato una riga con un valore maggiore di quello da cui sono partito, 
        sostituisco la riga di quest'utlimo con la riga del valore maggiore */
    if(row != k){
        vector<float> temp_one(m.at(k));
        m.at(k) = m.at(row);
        m.at(row) = temp_one;

        vector<float> temp_two(b.at(k));
        b.at(k) = b.at(row);
        b.at(row) = temp_two;
    }   
}

/* Algoritmo di Riduzione Gaussiana per il Sistema generalizzato Ax=b */
void riduzioneGaussiana(Matrice &coefficienti, Matrice &termineNoto){
    
    for (int k = 0; k < coefficienti.at(0).size() - 1; k++) {

        pivotingParziale(coefficienti, termineNoto, k);

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

/*
    ESERCIZIO 3
*/

/* Calcolo della matrice di perturbazione in base alla dimensione del vettore B termine noto */
Matrice matricePerturbazione(const int dim){

    Matrice perturbazione(dim, vector<float>(1));

    for(int i = 0; i < perturbazione.size(); i++){
        /* Nelle posizioni pari pongo come da specifiche il valore positivo, 
            altrimenti il valore negativo */
        if(i % 2 != 0) perturbazione.at(i).at(0) = 0.01;
        else perturbazione.at(i).at(0) = -0.01;
    }

    return perturbazione;
}

/* Calcolo del prodotto scalare n*m[i] */
Matrice prodottoScalare(const Matrice &m, int number){
    Matrice prod(m.size(), vector<float>(m.at(0).size()));

    for(int i = 0; i < prod.size(); i++){
        for(int j = 0; j < prod.at(0).size(); j++){
            prod.at(i).at(j) = m.at(i).at(j) * number;
        }
    }

    return prod;
}

/* Calcolo totale del temineNoto B pertubato come da specifiche */
Matrice perturbazioneTermineNoto(const Matrice &b, const Matrice &δb){

    Matrice result(b.size(), vector<float>(1));

    for(int i = 0; i < result.size(); i++)
        result.at(i).at(0) = b.at(i).at(0) + δb.at(i).at(0);
    
    return result;
}

/*
    FUNZIONI GENERICHE
*/

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