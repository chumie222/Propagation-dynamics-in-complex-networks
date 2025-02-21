clear all;
clc;

rep=100;    %重复次数
step=101;   %区间大小
N=10000;

data=load('F:\www\阈值模型\加媒体\mass media\SF\算极大联通子图\2.2\final_Infection.txt');% data=data(rep*step+1:rep*step*2);
% data=data(rep*step*2+1:rep*step*3);
% data_2=load('E:\www\Double Phase Tansition\C\SF\1,4\gamma=4\2\final_Infection.txt');
% data=[data;data_2];
data=data/N;

%  y=Variability(data,rep,step,N);
%  y=susceptible(data,rep,step,N);
  y=variance(data,rep,step,N);
 
hold on
plot(0:0.01:1,y);
dlmwrite('y.txt',y)