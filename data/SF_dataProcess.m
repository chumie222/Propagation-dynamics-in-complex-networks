clc;
clear;
networksize = 10000;
rho0 = 10;
T_A = 20;
T_B = 20;
A = 80;
B = 80;
v=20;

A_R_data = load([num2str(v) '/SF_Final_R_A_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_' num2str(rho0) '_v_' num2str(v) '.txt'], '-ascii'); 
theoretical_data = load([num2str(v) '/SF_theoretical_R_A_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_count_' num2str(rho0) '_v_' num2str(v) '.txt'], '-ascii');
once_range = 101;

firstA_seg = A_R_data(1:once_range, 1:2);

times = 1001;

A_all_segs = [];
for i=0:times-1
    A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/networksize];
end

[mean_A, square_variance, X_A] = modify_data(A_all_segs, times, 0.9);
mean_result_variance = [0:0.01:1; mean_A; square_variance]';
save([num2str(v) '/Mean_SF_Final_R_A_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_' num2str(rho0) '_v_' num2str(v) '.txt'], 'mean_result_variance', '-ascii');
X_A_result = [0:0.01:1; X_A]',
save([num2str(v) '/SF_X_A_v_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_' num2str(rho0) '_v_' num2str(v) '.txt'], 'X_A_result', '-ascii');


errorbar(0:0.01:1,mean_A,square_variance,'ob');
hold on
plot(0:0.01:1, theoretical_data(:,2),  'k--');
hold on
xlabel('\lambda');
ylabel('R_B');


hold on
% title(['�����������' num2str(q) ',������������,ER-ER����']);

