% ESERCIZIO 3 - Autovalori
% Andrea Franceschetti 4357070

clc; clear;

A = [1 -1 2; -2 0 5; 6 -3 6];

x = [1; 1; 1];

y = [3; 10; 4];

toll = 1e-10;
nmax = 1000;

% Calcolo del metodo delle potenze
[lambda1, eig_vect1, iter1] = potenze(A, x, toll, nmax);
fprintf('\n Il valore di lambda per [1, 1, 1] è: %2.5f \n', lambda1);
fprintf('\n Il numero di iterazioni per [1, 1, 1] è: %2.5f \n', iter1);
eig_vect1

[lambda2, eig_vect2, iter2] = potenze(A, y, toll, nmax);
fprintf('\n Il valore di lambda per [3, 10, 4] è: %2.5f \n', lambda2);
fprintf('\n Il numero di iterazioni per [3, 10, 4] è: %2.5f \n', iter2);
eig_vect2

% Calcolo della convergenza
conv = abs(lambda2) / abs(lambda1);
fprintf("La convergenza lambda2/lambda1 è: %2.5f \n", conv);

% Calcolo del metodo delle potenze inverse
disp("Metodo delle potenze inverse con mu = 4");
[lambda3, iter3] = potenzeInverse(A, 3, toll, 4, x, nmax);
fprintf('\n Il valore di lambda per mu = 4 è: %2.5f \n', lambda3);
fprintf('\n Il numero di iterazioni per mu = 4 è: %2.5f \n', iter3);

disp("Metodo delle potenze inverse con mu = 4.5");
[lambda4, iter4] = potenzeInverse(A,3, toll,4.5,y,nmax);
fprintf('\n Il valore di lambda per mu = 4.5 è: %2.5f \n', lambda4);
fprintf('\n Il numero di iterazioni per mu = 4.5 è: %2.5f \n', iter4);

% Calcolo della convergenza per il metodo delle potenze inverse
mu1 = 1 / (lambda3 - 4);
mu2 = 1 / (lambda4 - 4.5);
convInv = abs(mu2) / abs(mu1);
fprintf("La convergenza per il metodo delle potenze inverse e lambda2/lambda1 è: %2.5f \n", convInv);