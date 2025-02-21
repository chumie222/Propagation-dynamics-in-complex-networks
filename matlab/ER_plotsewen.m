clear;
clc;

T_A = 0;
a = 1;
b = a - 0.01;
seed_count = 10;

round_scale = 101;
R_data = [];

file_name = ['../data/' num2str(T_A) '/ER_all_theoretical_R_A_a_' num2str(a, '%.2f') '_seed_count_' num2str(seed_count) '.txt'];

R_all_theoretical_data = load(file_name, '-ascii');

for seed_index = 0:98
    range_data = seed_index * round_scale + 1:seed_index * round_scale + round_scale;
    R_data = [R_data; R_all_theoretical_data(range_data, 2)'];
end

y = 0:0.01:b; % x轴对应的b值
x = 0.01:0.01:1; % y轴对应的lambda值

figure;
imagesc(x, y, R_data); % 使用imagesc绘制2D图像
set(gca, 'YDir', 'normal'); % 使y轴方向正常显示
colorbar('location', 'EastOutside'); % 添加颜色条

xlabel('\lambda');
ylabel('b');
title('R(\infty)');