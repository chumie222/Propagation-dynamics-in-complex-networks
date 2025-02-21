clear all;
clc;

rep=100;    %重复次数
step=101;   %区间大小
N=10000;

data=load('F:\www\多关系网络上的协同传播\response physica a\er网络，ka不等于kb\ka=15,kb=10\final_Infection.txt');

 
% data=load('E:\www\多关系网络上的协同传播\C\ER无关联\cascade_step.txt');
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

%%%%%%%%%%画稳态密度%%%%%%%%%%%
% figure(23)

% subplot(2,1,1)
hold on
plot(0:0.01:1,r,'o')

dlmwrite('sim.txt',r)
% dlmwrite('sim.txt',[r fc])
%%%%%%%%%%画级联次数%%%%%%%%%%%
% hold on
% % subplot(2,1,2)
% plot(0:0.01:1,r)