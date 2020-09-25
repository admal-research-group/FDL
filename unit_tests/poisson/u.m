clear all
close all
clc
%% Specify File Names
timesteps=1000;
f = importdata('u.txt');
n = sqrt(size(f,1)/timesteps);
[X,Y] = meshgrid(1:1:n,1:1:n);
Z=zeros(n,n);
surf(X,Y,Z);
hold on;
k=1;
for l=1:timesteps
    for j=1:n
        for i=1:n
            Z(i,j)=f(k,3);
            k=k+1;
        end
    end
    if (mod(l,1)==0)
        hold all
        surf(X,Y,Z);
        pause(0.5);
    end
end