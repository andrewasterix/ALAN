#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <limits>
using namespace std;
typedef std::numeric_limits< double > dbl;

int main (){

    /* 
        ESERCIZIO 1 -  Calcolare (a + b) + c  e a + (b + c) dove:
        
        - a = (0 +1) * 10 ^ I
        - b = (7 +1) * 10 ^ 20
        - c = - ((7 +1) * 10 ^ 20)
        
        - D0 = 0 && D1 = 7 da numero di matricola: 4357070

    */
    
    const int D0 = 0;
    const int D1 = 7;

    /* Assegnazione Varibili */
    double a = 0.0;
    double b = (D1 + 1) * pow(10, 20);
    double c = -b;
    
    /* Per ogni valore di i eseguo i calcoli */
    for (int i = 0;i <= 6; i++){
        a += (D0 + 1) * pow(10, i);

        cout << "---------------------\n";
        cout << "Quanto i vale: " << i << endl;
        cout << "La varibile a: " << a << endl;
        cout << "La varibile b: " << b << endl;
        cout << "La varibile c: " << c << endl;
        cout << endl;
    
        double resultOne = (a + b) + c;
        double resultTwo = a + (b + c);

        cout << "La somma (a + b) + c : " << resultOne << endl;
        cout << "La somma a + (b + c) : " << resultTwo << endl;
        
        double error_abs_One = fabs(resultOne - a);
        double error_abs_Two = fabs(resultTwo - a);

        cout << "L'errore assoluto della somma (a + b) + c : " << error_abs_One << endl;
        cout << "L'errore assoluto della somma a + (b + c) : " << error_abs_Two << endl;

        double error_rel_One = error_abs_One / a;
        double error_rel_Two = error_abs_Two / a;

        cout << "L'errore relativo della somma (a + b) + c : " << error_rel_One<< endl;
        cout << "L'errore relativo della somma a + (b + c) : " << error_rel_Two << endl;
        
    }
   
    return 0;
}