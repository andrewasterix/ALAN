% ESERCIZIO 2 - Autovalori
% Andrea Franceschetti 4357070

clc; clear;

% Vettori dei Nodi e dei Pesi
S = [1 1 1 1 1 1 3 10 4 5 6 8 5 6];
T = [2 7 6 5 3 4 10 11 10 8 5 9 4 8];

% Generazione del grafo
G = graph(S, T);

% Generazione della matrice di adiacenza completa
A = full(adjacency(G));

% Vettori di zeri di lunghezza pari al numero di nodi
V = zeros(1, 11);

% Calcolo degli archi uscenti per ogni nodo
for i = 1:length(A(:,1))
   count = 0;
   for j = 1:length(A(1,:)) 
       if A(i,j)==1
           count = count+1;
       end
   end
   V(i) = count;
end

% Matrice D diagonalizzata di V
D = diag(V);

% Matrice G come da specifiche
G = A*inv(D);

[autovettori,autovalori] = eig(G);