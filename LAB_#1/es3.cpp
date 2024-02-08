#include <iostream>
#include <math.h>
using namespace std;

/*
    ESERCIZIO 3 - Determinare la precisione di macchina eps: 
        - eps = 2^-d; 
        - d è il più gradnde intero positivo tale che 1 + 2^-d > 1;
        - valore risultante in singola e doppia precisione 
*/

template <typename T> 
T precisioneMacchina()
{
    T precision = 0;
	T eps = 1;
    int d = 0;
	
    for(; 1+eps > 1; d++){
		
        eps = pow(2,-d);
		
        if(1+eps == 1) precision = d-1;
	}
	return precision;
}

int main(int argc, char const *argv[])
{
    float singolaPrecisione = precisioneMacchina<float>();
    double doppiaPrecisione = precisioneMacchina<double>();
    
    cout << "Singola precisione: Valore di d: " << singolaPrecisione << " => eps: 2^" << singolaPrecisione << " = " << pow(2 , -singolaPrecisione) << endl;
    cout << "Doppia precisione: Valore di d: " << doppiaPrecisione << " => eps: 2^" << doppiaPrecisione << " = " << pow(2,-doppiaPrecisione) << endl;
    return 0;
}
