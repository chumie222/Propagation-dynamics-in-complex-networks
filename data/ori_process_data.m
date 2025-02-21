function [ mean_A, square_variance, X_A ] = ori_process_data( A_all_segs, times)
%ORI_PROCESS_DATA 此处显示有关此函数的摘要
%   此处显示详细说明
mean_A = sum(A_all_segs)/times; %A平均值
variance_A = A_all_segs-repmat(mean_A,times, 1);
variance_A = variance_A.^2;
variance_A = sum(variance_A) / times;

square_variance = variance_A.^0.5;
mean_A_square = mean_A.^2;

X_A = variance_A./mean_A_square;
end

