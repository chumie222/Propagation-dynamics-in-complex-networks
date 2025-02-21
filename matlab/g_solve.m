clear all
clc;

global degree q lambda_A r T_A T_B rho_0 thetaB

data=load('combined_degree.nw');
max_degree=max(max(data(:,1)),max(data(:,2)));
network_size=10000;

combined_degree = spconvert(data);
combined_degree(max_degree,max_degree) = 0;
combined_degree = full(combined_degree);

degree=[];
count=0;
q = 0.9;
lambda_A=0.2;
lambda_B=lambda_A;
color = 'b';
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
 
r=1;
T_A=1;
T_B=3;

rho_0=0.0001;
temp_R=[];

for thetaB=1:-0.01:0
    
    disp(['lambda_A is ' num2str(lambda_A) ', q is ' num2str(q) ', thetaB1 is' num2str(thetaB)]);
   
    [ thetaA1, time ] = Steff(1);
    if thetaA1>1
        continue;
    end
    
    temp_R=[temp_R; [thetaB1 thetaA1]];
    
end
file_name = sprintf("thetaB_thetaA_lambda_%.2f_q_%.2f.nw", lambda_A, q);
save(file_name, 'temp_R', '-ascii');
plot(temp_R(:,2)', temp_R(:,1)');
hold on

% temp_R1=[];
% for thetaA2=1:-0.01:0
%     
%     disp(['lambda_A is ' num2str(lambda_A) ', q is ' num2str(q) ', betaA2 is' num2str(thetaA2)]);
%    
%     thetaB2 = f_B(lambda_A, lambda_B, r, T_A, T_B, rho_0, degree, q, thetaA2)
%     if thetaB2>1
%         continue;
%     end
%     temp_R1=[temp_R1; [thetaA2 thetaB2]];
% end
% file_name = sprintf("thetaA_thetaB_lambda_%.2f_q_%.2f.nw", lambda_A, q);
% save(file_name, 'temp_R1', '-ascii');
% plot(temp_R(:,2)', temp_R(:,1)');
% hold on
% plot(temp_R1(:,1)', temp_R1(:,2)');
% xlabel('\theta A')
% ylabel('\theta B')