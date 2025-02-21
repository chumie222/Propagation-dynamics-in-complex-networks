clear all
clc;

global degree q lambda_A lambda_B  r T_A T_B rho_0

data=load('combined_degree.nw');
max_degree=max(max(data(:,1)),max(data(:,2)));
network_size=10000;

combined_degree = spconvert(data);
combined_degree(max_degree,max_degree) = 0;
combined_degree = full(combined_degree);

rho_0 = 0.0001;
r = 1;
T_A = 1;
T_B = 3;
degree=[];
count=0;
q = 0.9;
lambda_A=0.2;
lambda_B=lambda_A;
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

ezplot(GA,[0,1]);