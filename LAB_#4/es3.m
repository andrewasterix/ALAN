% ESERCIZIO 3 - SVD
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

for j=1:m 
    y(j) = sin(j/m);
end

A(:,3)= A(:,3).^2;
y = y.';

disp("Risoluzione di Ac = y con SVD");
[U,S,V] = svd(A, 0);
c = V*((U'*y)./diag(S));
disp(c);

disp("Risoluzione di Ac = y con QR");
[Q, R] = qr(A);
c = R\Q.'*y;
disp(c);

disp("Risoluzione di Ac = y con A'Ac = A'y");
temp1 = A.'*A;
temp2 = A.'*y;
c = temp1\temp2;
disp(c);

disp("Risoluzione di Ac = y con c = A\y");
c = A\y;
disp(c);
