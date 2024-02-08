% Esercizio 2 - SVD
% Andrea Franceschetti 4357070

clc; clear;

n=0;

for index = 1:5

    n = n+5;
    
    fprintf('Matrice di taglia nxn con n=%d \n', n);
    
    for i = 1:n
        for j = 1:n
            if i == j
                out(i,j) = 1;
            elseif i < j
                out(i,j) = -1;
            elseif i >j
                out(i,j) = 0;
            end
        end
    end
    
    disp("Valori singolari");
    [U,S,V] = svd(out);
    Vect = diag(out);
    disp(Vect);

    disp("Condizionamento in norma 2");
    disp(cond(out,2));
    
    disp("Perturbazione in A(n,1) di -2^(2-n)");
    disp("Autovalori della matrice perturbata");
    out(n,1) = out(n,1)-2^(2-n);
    W = eig(out);
    disp(W);
end