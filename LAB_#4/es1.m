% ESERCIZIO 1 - SVD
% Andrea Franceschetti 4357070

clc; clear;

% Valore di m
d0 = 0;
d1 = 7;
m = 10*(d0 + 1) + d1;

% Matrice A
for i = 1:m
    A(i,1) = 1;
    A(i,2) = i/m;
    A(i,3) = (i/m).^2;
end

% ESERCIZIO 1 A
SA = svd(A);
Vect = diag(SA);
disp("Decomposizione a valori singolari di A");
disp(Vect);

SAt = svd(A');
disp("Decomposizione a valori singolari di A'");
Vect = diag(SAt);
disp(Vect);

% ESERCIZIO 1 B
disp("Autovalori di AA'");
Vect = eig(A*A.');
disp(Vect);

disp("Autovalori di A'A");
Vect = eig(A.'*A);
disp(Vect);

% ESERCIZIO 1 C
disp("Immagine di A, da confrontare con U");
Im1 = orth(A);
disp(Im1);

disp("Immagine di A' da confrontare con U");
Im2 = orth(A');
disp(Im2);

% ESERCIZIO 1 D
disp("Ker di A, da confrontare con V'");
Ker1 = null(A);
disp(Ker1);

disp("Ker di A' da confrontare con V'");
Ker2 = null(A');
disp(Ker2);