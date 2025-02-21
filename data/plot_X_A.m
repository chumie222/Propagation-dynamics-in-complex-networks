clc;
clear;

rho0 = 10;
T_A_array = [20, 50, 80];
T_B = T_A_array;
color = ['r', 'g', 'b'];
A = 80;
B = 80;
for index = 1:3
    T_A = T_A_array(index);
    filename_simulation = [num2str(T_B) '/Mean_ER_Final_R_A_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_' num2str(rho0) '.txt']
    filename_theory = [num2str(T_B) '/ER_theoretical_omega_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_count_' num2str(rho0) '.txt']
    filename_chi = [num2str(T_B) '/X_A_omega_TA_' num2str(T_A) '_TB_' num2str(T_B) '_A_' num2str(A) '_B_' num2str(B) '_seed_' num2str(rho0) '.txt']
    A_R_data = load(filename_simulation, '-ascii'); 
    theoretical_data = load(filename_theory, '-ascii');
    X_A = load(filename_chi, '-ascii');   
    subplot(2,1,1)
    errorbar(A_R_data(:,1)',A_R_data(:,2)',A_R_data(:,3)',['o' color(index)]);
    hold on
    plot(0:0.01:1, theoretical_data(:,2),  [color(index) '--']);
    hold on
    xlabel('\beta');
    ylabel('R(\infty)');

    subplot(2,1,2)
    plot(X_A(:,1)', X_A(:,2)', color(index));
    xlabel('\beta');
    ylabel('\chi');
    hold on
end




