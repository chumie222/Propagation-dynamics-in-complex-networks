clear all;
clc;

rep=100;    %�ظ�����
step=101;   %�����С
N=10000;

data=load('F:\www\��ֵģ��\��ý��\mass media\SF\�㼫����ͨ��ͼ\2.2\final_Infection.txt');% data=data(rep*step+1:rep*step*2);
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