clear all
close all
clc
%% Specify File Names
f = importdata('u.txt');
[X,Y] = meshgrid(1:1:38,1:1:38);
k=1;
for j=1:38
    for i=1:38
        Z(i,j)=f(k,3);
        k=k+1;
    end
end
surf(X,Y,Z);