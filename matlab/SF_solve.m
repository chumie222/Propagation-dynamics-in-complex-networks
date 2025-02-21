clear all
clc;

global lambda_A lambda_B r_A r_B T_A T_B A_a B_a A B A_b B_b rho_0 degree degree_A degree_B

%y是theta_w_A和theta_w_B的串联

r_A=1;
r_B=1;
T_A=10;
T_B=10;
A_a = T_A*0.01;
B_a = T_B*0.01;
A = 80;
B = 80;
A_b = A*0.01;
B_b = B*0.01;
v=20;
seed_count = 10;

filename = ['../data/' num2str(v) '/SF_combined_degree_TB_' num2str(T_B) '_B_' num2str(B) '_v_' num2str(v) '.txt']
data=load(filename);
max_degree=max(max(data(:,1)),max(data(:,2)));
network_size=10000;
degree_A=load(['../data/' num2str(v) '/SF_A_degree_distribution_TB_' num2str(T_B) '_B_' num2str(B) '_v_' num2str(v) '.txt']);
degree_B=load(['../data/' num2str(v) '/SF_B_degree_distribution_TB_' num2str(T_B) '_B_' num2str(B) '_v_' num2str(v) '.txt']);
%filename = ['../data/' num2str(v) '/SF_SF_combined_degree_v_' num2str(v) '.txt'];
%做成全阵，再取出分布非零的项，排除孤立点的情况，因为如果有孤立点，则其度为0，spconvert(data)会报错
%len_degree_A = length(degree_A);
%len_degree_B = length(degree_B);
combined_degree = spconvert(data);
combined_degree(max_degree,max_degree) = 0;
combined_degree = full(combined_degree);

degree=[];
for i=1:max_degree
   for j=1:max_degree
       degree = [degree; [i,j,combined_degree(i,j)]];
   end    
end

temp=[];
for i=1:length(degree)
    if degree(i,3)>0
        temp=[temp;degree(i,:)];
    end
end
degree=temp;
len_degree = length(degree);

R=[];
avg_K_A=sum(degree_A(:,1).*degree_A(:,2));
avg_K_B=sum(degree_B(:,1).*degree_B(:,2));

rho_0=seed_count*0.0001;
temp_R=[];
for lambda_A=0.01:0.01:1
    disp(['lambda_A is ' num2str(lambda_A)]);
    lambda_B=lambda_A;
    %初始值是theta_w_A和theta_w_B的两个列向量
    [TT,YY]=ode23(@thresholdModel, 0:100, ones(len_degree+len_degree,1));
    [x,y]=size(YY);
    theta_A_B_w=YY(x,:);  %%%%last line of YY (value in stable state)
    theta_A=0;
    theta_B=0;
    
    %计算theta_A
    for w=1:len_degree
        theta_A=theta_A+(degree(w,1)*degree(w,3)/avg_K_A)*theta_A_B_w(w);
    end
    
    %计算theta_B
    for w=1:len_degree
        theta_B=theta_B+(degree(w,2)*degree(w,3)/avg_K_B)*theta_A_B_w(w+len_degree);
    end

    s=0;
    
    for kk=1:length(degree)
        s=s+degree(kk,3)*susceptible_K(kk,theta_A,theta_B);
    end
%         dlmwrite('R_A=3,R_B=4.txt',1-s,'-append');
  
    temp_R=[temp_R 1-s]
end
R=[R; temp_R];
ER_3D_temp = [0:0.01:1; [seed_count*0.0001, R]]';
file_name =['../data/' num2str(v) '/SF_theoretical_R_A_TA_' num2str(T_A)  '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_count_' num2str(seed_count) '_v_' num2str(v) '.txt'];
save(file_name,'ER_3D_temp','-ascii');