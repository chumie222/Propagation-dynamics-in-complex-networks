clear;
clc;

T_A=10;
T_B=10;
v = 21;
seed_count = 10;

round_scale = 101; %一次种子对应101个lambda
R_data = [];
%rho_0_critical = [0.003, 0.03, 0.06];
file_name =['../data/' num2str(v) '/ER_all_theoretical_R_A_a_' num2str(a,'%.2f') '_seed_count_' num2str(seed_count) '.txt'];
R_all_theoretical_data = load(file_name, '-ascii');
for seed_index = 0:99
    range_data = seed_index*round_scale+1:seed_index*round_scale+round_scale;
    R_data = [R_data; R_all_theoretical_data(range_data,2)'];
end

[x,y] = meshgrid(0:0.01:1, 0.01:0.01:1);
size([x,y])
surf(x,y,R_data);
colorbar('location','EastOutside')

%hold on
%plot3(0:0.01:1, ones(1,101)*rho_0_critical(T_B), ones(1,101)*2, 'w--', 'linewidth',2)

% hold on
% plot3(beta_c_d_2(:,1), beta_c_d_2(:,2), beta_c_d_2(:,3), 'r^-')
% hold on
% plot3(beta_c_d_1(:,1), beta_c_d_1(:,2), beta_c_d_1(:,3), 'wo-')
% hold on
% plot3(connect_line(:,1), connect_line(:,2), connect_line(:,3), 'w-')

xlabel('\lambda');
ylabel('\beta')
zlabel('R(\infty)')
shading interp;