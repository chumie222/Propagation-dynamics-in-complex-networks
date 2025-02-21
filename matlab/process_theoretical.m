clc;
clear;

all_result = [];

% for q=0:100:10000
%     file_name = sprintf('../data/ER_Final_R_A_q_%d',q);
%     A_R_data = load(file_name, '-ascii');
% %     file_name = sprintf('../data/ER_Final_R_B_q_%d',q);
% %     B_R_data = load(file_name, '-ascii');
% 
%     once_range = 101;
% 
%     firstA_seg = A_R_data(1:once_range, 1:2);
% %     firstB_seg = B_R_data(1:once_range, 1:2);
% 
%     times = 10000;
% 
%     A_all_segs = [];
% %     B_all_segs = [];
%     for i=0:times-1
%         A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
% %         B_all_segs = [B_all_segs; B_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
%     end
% 
%     mean_A = sum(A_all_segs)/times; %A平均值
% %     mean_B = sum(B_all_segs)/times; %B平均值
% 
%     A_mean_value_matrix = repmat(mean_A, times, 1);
% %     B_mean_value_matrix = repmat(mean_B, times, 1);
% 
%     A_logical_values = A_all_segs>=A_mean_value_matrix;
% %     B_logical_values = B_all_segs>=B_mean_value_matrix;
%     A_all_segs(~A_logical_values) = 0;
% %     B_all_segs(~B_logical_values) = 0;
% 
%     A_all_segs = sum(A_all_segs)./sum(A_logical_values);
%     temp = [ones(1,101)*q*0.0001; 0:0.01:1; A_all_segs]';
% %     B_all_segs = sum(B_all_segs)./sum(B_logical_values);
%     all_result = [all_result; temp];
% end
% save('er_R_q_lambda.txt', 'all_result', '-ascii');

all_result = load('er_R_q_lambda.txt','-ascii');

total_data = reshape(all_result(:,3), 101, 101);
[x,y] = meshgrid(0:0.01:1, 0:0.01:1);
surf(x,y,total_data');
colorbar('location','EastOutside')
xlabel('\lambda');
ylabel('q');
shading interp;
