clc;
clear;
networksize = 10000;
rho0 = 1000;
alpha_omega_A = 30;
alpha_omega_B = 30;
TA = 1;
TB = 1;
v=40;
c = 8;
theoretical_data = load([num2str(v) '/ER_theoretical_R_A_TA_' num2str(TA) '_TB_' num2str(TB) '_seed_count_' num2str(rho0) '_v_' num2str(v) '_c_' num2str(c) '.txt'], '-ascii');
once_range = 101;

plot(0:0.01:1, theoretical_data(:,2),  'k--');
hold on
xlabel('\lambda');
ylabel('R_B');

% title(['积极个体比例' num2str(q) ',都是消极个体,ER-ER网络']);

