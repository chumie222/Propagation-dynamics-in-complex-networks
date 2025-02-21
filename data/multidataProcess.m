clc;
clear;

% q =2000;
all_mean_values = [];
all_relative_value = [];
total_loops = 14;
internal_loop_length = 2000;
for q=1000:100:10000
    q
    A_R_data = [];
    B_R_data = [];

    for dir_index=0:total_loops-1
        A_R_data = [A_R_data; load([num2str(dir_index) '/ER_Final_R_A_q_' num2str(q) '_' num2str(dir_index)], '-ascii')];  
    end

    once_range = 101;

    firstA_seg = A_R_data(1:once_range, 1:2);

    times = total_loops*internal_loop_length;

    A_all_segs = [];
    for i=0:times-1
        A_all_segs = [A_all_segs; A_R_data(i*once_range+1:(i+1)*once_range, 3)'/10000];
    end

    %计算平均值
    mean_A = sum(A_all_segs)/times; %A平均值

    A_mean_value_matrix = repmat(mean_A, times, 1);

    A_logical_values = A_all_segs>=A_mean_value_matrix;
    A_all_segs(~A_logical_values) = 0;
    valid_A_data = A_all_segs;

    A_all_segs = sum(A_all_segs)./sum(A_logical_values);
    all_mean_values = [all_mean_values;A_all_segs];

    %计算方差
    variance_A = valid_A_data-repmat(A_all_segs,times, 1);
    variance_A = variance_A.^2;
    variance_A(~A_logical_values) = 0;
    variance_A = sum(variance_A)./sum(A_logical_values);

    error_values = variance_A.^0.5;

%     temp = [0:0.01:1; A_all_segs; error_values]';

    %计算相对波动方差
    mean_A_square = A_all_segs.^2;
    X_A = variance_A./mean_A_square;
    all_relative_value = [all_relative_value; X_A];
%     temp = [0:0.01:1; X_A]';

end
    save(['ER_R_all_mean_variance_.txt'],'all_mean_values','-ascii');
    save(['X_A_.txt'],'all_relative_value','-ascii');
% title(['积极个体比例' num2str(q) ',都是消极个体,ER-ER网络']);

