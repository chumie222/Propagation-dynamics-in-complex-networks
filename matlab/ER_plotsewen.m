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

y = 0:0.01:b; % x���Ӧ��bֵ
x = 0.01:0.01:1; % y���Ӧ��lambdaֵ

figure;
imagesc(x, y, R_data); % ʹ��imagesc����2Dͼ��
set(gca, 'YDir', 'normal'); % ʹy�᷽��������ʾ
colorbar('location', 'EastOutside'); % �����ɫ��

xlabel('\lambda');
ylabel('b');
title('R(\infty)');