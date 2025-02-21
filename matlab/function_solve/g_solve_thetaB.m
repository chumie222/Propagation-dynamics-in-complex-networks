clear all
clc;
global degree q lambda_B r T_A T_B rho_0 thetaA thetaB
data=load('../combined_degree.nw');
max_degree=max(max(data(:,1)),max(data(:,2)));
network_size=10000;

combined_degree = spconvert(data);
combined_degree(max_degree,max_degree) = 0;
combined_degree = full(combined_degree);

degree=[];
count=0;
q = 0.12;
lambda_A=0.95;
lambda_B=lambda_A;
initial_value =0.9;
color = 'r';
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
for thetaA=0:0.01:1
     [ thetaB, time ] = SteffB(initial_value);
%     if abs(thetaB2)>1
%         continue;
%     end
    temp_R=[temp_R; [thetaA thetaB]];
    disp([num2str(thetaA) ' ' num2str(thetaB)]);
end
file_name = sprintf("thetaA_thetaB_lambda1_%.3f_q_%.3f.nw", lambda_A, q)
save(file_name, 'temp_R', '-ascii');

% temp_R1=[];
% for thetaB=0:0.01:1
%      [ thetaA, time ] = SteffB2(initial_value);
% %     if abs(thetaB2)>1
% %         continue;
% %     end
%     temp_R1=[temp_R1; [thetaB thetaA]];
%     disp(['lambda_A is ' num2str(lambda_A) ', q is ' num2str(q) ', thetaA is' num2str(thetaA) ',thetaB is ' num2str(thetaB)]);
% end
% file_name = sprintf("thetaA_thetaB_lambda2_%.2f_q_%.2f.nw", lambda_A, q);
% save(file_name, 'temp_R1', '-ascii');
plot(temp_R(:,1)', temp_R(:,2)', [ color '-.']);
hold on
% plot(temp_R1(:,2)', temp_R1(:,1)', 'ro');
xlabel('\theta_A')
ylabel('\theta_B')
axis([0,1,0,1])