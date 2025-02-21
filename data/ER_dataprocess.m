clc;
clear;
networksize = 10000;
rho0 = 10;
a=1.0;
b=0.01;
T_B = 0; %修改参数%
B = 80;%修改参数%

A_R_data = load([num2str(T_B) '/ER_Final_R_A_a_' num2str(a,'%.2f') '_b_' num2str(b,'%.2f') '_seed_' num2str(rho0) '.txt'], '-ascii'); 
theoretical_data = load([num2str(T_B) '/ER_theoretical_R_A_a_' num2str(a,'%.2f') '_b_' num2str(b,'%.2f') '_seed_count_' num2str(rho0) '.txt'], '-ascii');
once_range = 101;

firstA_seg = A_R_data(1:once_range, 1:2);

times = 1001;

A_all_segs = [];
for i=0:times-1
    A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/networksize];
end

[mean_A, square_variance, X_A] = modify_data(A_all_segs, times, 0.9);
mean_result_variance = [0:0.01:1; mean_A; square_variance]';
save([num2str(T_B) '/Mean_ER_Final_R_A_a_' num2str(a,'%.2f') '_b_' num2str(b,'%.2f') '_seed_' num2str(rho0) '.txt'], 'mean_result_variance', '-ascii');
X_A_result = [0:0.01:1; X_A]',
save([num2str(T_B) '/ER_X_A_a_' num2str(a,'%.2f') '_b_' num2str(b,'%.2f') '_seed_' num2str(rho0) '.txt'], 'X_A_result', '-ascii');


errorbar(0:0.01:1,mean_A,square_variance,'ob');
hold on
plot(0:0.01:1, theoretical_data(:,2),  'k--');
hold on
xlabel('\lambda');
ylabel('R_B');


hold on
% title(['积极个体比例' num2str(q) ',都是消极个体,ER-ER网络']);