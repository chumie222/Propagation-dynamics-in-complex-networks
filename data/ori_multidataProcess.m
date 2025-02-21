clc;
clear;

q =1500;
A_R_data = [];
% B_R_data = [];
total_loops = 14;
internal_loop_length = 2000;
for dir_index=0:total_loops-1
    A_R_data = [A_R_data; load([num2str(dir_index) '/ER_Final_R_A_q_' num2str(q) '_' num2str(dir_index)], '-ascii')];
%     B_R_data = [B_R_data; load([num2str(dir_index) '/ER_Final_R_B_q_' num2str(q) '_' num2str(dir_index)], '-ascii')];    
end

once_range = 101;

firstA_seg = A_R_data(1:once_range, 1:2);
% firstB_seg = B_R_data(1:once_range, 1:2);

times = total_loops*internal_loop_length;

A_all_segs = [];
B_all_segs = [];
for i=0:times-1
    A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
%     B_all_segs = [B_all_segs; B_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
end

mean_A = sum(A_all_segs)/times; %A平均值
% mean_B = sum(B_all_segs)/times; %B平均值

% A_mean_value_matrix = repmat(mean_A, times, 1);
% B_mean_value_matrix = repmat(mean_B, times, 1);
% 
% A_logical_values = A_all_segs>=A_mean_value_matrix;
% B_logical_values = B_all_segs>=B_mean_value_matrix;
% A_all_segs(~A_logical_values) = 0;
% B_all_segs(~B_logical_values) = 0;
% valid_A_data = A_all_segs;
% valid_B_data = B_all_segs;
% 
% A_all_segs = sum(A_all_segs)./sum(A_logical_values);
% B_all_segs = sum(B_all_segs)./sum(B_logical_values);


variance_A = A_all_segs - repmat(mean_A,times, 1);
variance_A = variance_A.^2;
variance_A = sum(variance_A)./times;
% variance_A = valid_A_data-repmat(A_all_segs,times, 1);
% variance_A = variance_A.^2;
% variance_A(~A_logical_values) = 0;
% variance_A = sum(variance_A)./sum(A_logical_values);


subplot(2,1,1)
% plot(0:0.01:1, mean_A, 'k--');
error_values = variance_A.^0.5;

%temp = [0:0.01:1; A_all_segs; error_values]';

temp = [0:0.01:1; mean_A; error_values]';
% save(['ER_R_mean_variance_q_' num2str(q) '.txt'],'temp','-ascii');
errorbar(0:0.01:1, mean_A, error_values, 'ko');
hold on
% theoretical = load(['ER_theoretical_q_' num2str(q) '.txt'], '-ascii');
% plot(0:0.01:1, theoretical(:,2)', 'k--');
% hold on
xlabel('\lambda');
ylabel('R_B');

mean_A_square = mean_A.^2;

X_A = variance_A./mean_A_square;
subplot(2,1,2)
plot(0:0.01:1, X_A, 'k');
hold on
temp = [0:0.01:1; X_A]';
save(['X_A_q_' num2str(q) '.txt'],'temp','-ascii');
% title(['积极个体比例' num2str(q) ',都是消极个体,ER-ER网络']);

