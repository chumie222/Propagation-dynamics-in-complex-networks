clear all;
clc;

rep=100;    %�ظ�����
step=101;   %�����С
N=10000;

data=load('F:\www\���ϵ�����ϵ�Эͬ����\response physica a\er���磬ka������kb\ka=15,kb=10\final_Infection.txt');

 
% data=load('E:\www\���ϵ�����ϵ�Эͬ����\C\ER�޹���\cascade_step.txt');
data=data/N;
% data=data(length(data)/2+1:length(data));
 
temp_r=zeros(step,rep);
for i=1:rep
    temp_r(:,i)=data((i-1)*step+1:i*step);
end

r=zeros(step,1);
fc=zeros(step,1);
for i=1:step
    r(i)=mean(temp_r(i,:));
    fc(i)=std(temp_r(i,:));
end

%%%%%%%%%%����̬�ܶ�%%%%%%%%%%%
% figure(23)

% subplot(2,1,1)
hold on
plot(0:0.01:1,r,'o')

dlmwrite('sim.txt',r)
% dlmwrite('sim.txt',[r fc])
%%%%%%%%%%����������%%%%%%%%%%%
% hold on
% % subplot(2,1,2)
% plot(0:0.01:1,r)