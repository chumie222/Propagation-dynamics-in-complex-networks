clc;
clear;

q =1000;

A_R_data = load(['SF_Final_R_A_q_' num2str(q) '_v_2.1' ], '-ascii');
B_R_data = load(['SF_Final_R_B_q_' num2str(q) '_v_2.1' ], '-ascii');

once_range = 101;

firstA_seg = A_R_data(1:once_range, 1:2);
firstB_seg = B_R_data(1:once_range, 1:2);

times = 1000;

A_all_segs = [];
B_all_segs = [];
for i=0:times-1
    A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
    B_all_segs = [B_all_segs; B_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
end

mean_A = sum(A_all_segs)/times; %A平均值
mean_B = sum(B_all_segs)/times; %B平均值

A_mean_value_matrix = repmat(mean_A, times, 1);
B_mean_value_matrix = repmat(mean_B, times, 1);

A_logical_values = A_all_segs>=A_mean_value_matrix;
B_logical_values = B_all_segs>=B_mean_value_matrix;
A_all_segs(~A_logical_values) = 0;
B_all_segs(~B_logical_values) = 0;
valid_A_data = A_all_segs;
valid_B_data = B_all_segs;

A_all_segs = sum(A_all_segs)./sum(A_logical_values);
B_all_segs = sum(B_all_segs)./sum(B_logical_values);

subplot(2,1,1)
plot(0:0.01:1, A_all_segs, 'go');
hold on
% plot(0:0.01:1, mean_B, 'rs');
% hold on
xlabel('\lambda');
ylabel('R_B');

subplot(2,1,2)
variance_A = valid_A_data-repmat(A_all_segs,times, 1);
variance_A = variance_A.^2;
variance_A(~A_logical_values) = 0;
variance_A = sum(variance_A)./sum(A_logical_values);

mean_A_square = A_all_segs.^2;

X_A = variance_A./mean_A_square;

subplot(2,1,2)
plot(0:0.01:1, X_A, 'g');
hold on
% title(['积极个体比例' num2str(q) ',都是消极个体,ER-ER网络']);

