function [lambda, eig_vect, iter] = potenze(A, x, toll, nmax)
% OUTPUT
% lambda   : autovalore calcolato;
% eig_vect : autovettore calcolato;
% iter     : numero di iterazioni per arrivare a convergenza;

% INPUT
% A        : matrice;
% x        : vettore iniziale;
% toll     : tolleranza;
% nmax     : numero massimo di iterazioni;

iter = 0;
lambda = 1;

for i = 1: nmax
    eig_vect = A * x;
    
    % Normalizzazione
    mx = max(abs(eig_vect));
    x = eig_vect / mx;

    % Valutazione dell'errore
    err = abs(lambda - mx);
    lambda = mx;

    if err <= toll
        break
    end
    iter = i;
end
end