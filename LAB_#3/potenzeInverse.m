function [lambda , iter] = potenzeInverse(A , n, toll , mu, x0 , nmax )
% OUTPUT 
% lambda   : autovalore calcolato;
% iter     : numero di iterazioni per arrivare a convergenza;

% INPUT
% A        : matrice;
% n        : dimensione matrice
% toll     : tolleranza;
% mu       : parametro per la matrice Identità
% x0       : vettore iniziale;
% nmax     : numero massimo di iterazioni;

iter = 0;

q = x0 / norm ( x0 );
lambda = q.'* A * q ;
flag = true;

while(flag)
    iter = iter + 1;
    [L , U , P ] = lu ( A - mu * eye ( n ),'matrix');
    x_old = q ;
    l_old = lambda ;
    y = L \P * q ;
    x = U \y ;

    q = x / norm ( x );
    lambda = q.' * A * q ;
    
    flag = and(abs(lambda - l_old) >= toll * abs (lambda), (iter <= nmax));
end
end