% ESERCIZIO 1 - Autovalori
% Andrea Franceschetti 4357070

clc; clear;

d0 = 0;
d1 = 7;
n = 10*(d1 + 1) + d0;

% Matrice A (Blocco di Jordan
A = diag(ones(1, n-1), 1) + eye(n);

% Matrice E
E = zeros(n);
E(n, 1) = 2^(-n);

% Matrice B
B = A + E;

% Calcolo manuale degli autovalori di A e B
syms lambda;
SA = double(solve(det(A-lambda*eye(n))==0, lambda))
SB = double(solve(det(B-lambda*eye(n))==0, lambda))

% Calcolo automatico degli autovalori di A e B
VA = eig(A)
VB = eig(B)

% Confronto puntale dei valori
resA = isequal(SA,VA)
resB = isequal(SB,VB)

% Confronto degli autovalori in Norma
normaBA = norm(B - A) / norm(A)
normaVAVB = norm(VB - VA) / norm(VA)

% Ripetizione Esercizio per AtA e BtB
At = A';
Bt = B';

SAt = double(solve(det(At-lambda*eye(n))==0, lambda))
SBt = double(solve(det(Bt-lambda*eye(n))==0, lambda))

% Calcolo automatico degli autovalori di A e B
VAt = eig(At)
VBt = eig(Bt)

% Confronto puntale dei valori
resAt = isequal(SAt,VAt)
resBt = isequal(SBt,VBt)

% Confronto degli autovalori in Norma
normaAtA = norm(At - A) / norm(A)
normaBtB = norm(Bt - B) / norm(B)

normaVAtAt = norm(VAt - VA) / norm(VA)
normaVBtBt = norm(VBt - VB) / norm(VB)