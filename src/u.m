clear all
close all
clc
%% Specify File Names
f = importdata('u.txt');
n = sqrt(size(f,1));
[X,Y] = meshgrid(1:1:n,1:1:n);
k=1;
for j=1:n
    for i=1:n
        Z(i,j)=f(k,3);
        k=k+1;
    end
end
surf(X,Y,Z);