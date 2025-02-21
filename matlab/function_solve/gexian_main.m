clc;
clear;
[x,time]=gexian('2*exp(2*x)-7*x^2-10',-2,2)
x=-2:0.01:2;
e=exp(1);
y=2*e.^(2*x)-7*x.^2-10;
plot(x,y)
grid on