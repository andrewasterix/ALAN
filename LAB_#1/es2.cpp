#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

double fact(double number);
double taylor (double x, int N);

double err_assoluto(double x_err, double x);
double err_relativo(double x_err, double x);

const int algTwoDim = 2;
const int dimX = 4;
const int dimN = 5;

double x[dimX] = {0.5, 30.0, -0.5, -30.0};
double N[dimN] = {3, 10, 50, 100, 150};

int main(int argc, char const *argv[])
{
    double x_exp, x_err;

    cout << "---- Algoritmo 1 ----\n";
    for (int i = 0; i < dimX; i++)
    {
        for (int j = 0; j < dimN; j++)
        {
            cout << "x= " << x[i] << " N= " << N[j] << endl;

            x_exp = exp(x[i]);
            x_err = taylor(x[i], N[j]);

            cout << "exp(x) = " << x_exp << endl;
            cout << "Fn(x) = " << x_err << endl;
            cout << "Errore Assoluto = " << x_err - x_exp << endl;
            cout << "Errore Relativo = " << (x_err - x_exp) /x_exp << endl;
            cout << endl;
        }
            
    }
    
    cout << "---- Algoritmo 2 ----\n";
        
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < dimN; j++)
        {
            cout << "x= -" << x[i] << " N= " << N[j] << endl;

            x_exp = exp(-x[i]);
            x_err = 1/taylor(x[i], N[j]);

            cout << "exp(x) = " << x_exp << endl;
            cout << "1/Fn(x) = " << x_err << endl;
            cout << "Errore Assoluto = " << x_err - x_exp << endl;
            cout << "Errore Relativo = " << (x_err - x_exp) /x_exp << endl;
            cout << endl;
        }        
    }
    
    return 0;
}

double fact (double number){
    if(number == 1) return 1;
    return number * fact(number - 1);
}

double taylor (double x, int N){

    /*
        Polinomio di Taylor: Fn(x) = ∑(n = 0 -> N) x^n / n!
    */

    if(N == 0) return 1;
	if(N == 1) return x+1;
    return taylor(x, N - 1) + pow(x, N) / fact(N);
}