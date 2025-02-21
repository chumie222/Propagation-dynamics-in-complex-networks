function [ new_mean_value,  square_variance, X_A] = modify_data(original_data, total_count, coefficient)
%MODIFY_DATA 此处显示有关此函数的摘要
%   此处显示详细说明
% A_all_segs = original_data;
original_mean_value = sum(original_data)/total_count; %原始平均值
mean_matrix = repmat(original_mean_value, total_count, 1);
original_data(original_data<mean_matrix*coefficient) = 0;

%每一列求平均值
logical_pattern = original_data~=0;
new_mean_value = sum(original_data)./sum(logical_pattern);

mean_matrix_averaged = repmat(new_mean_value,total_count,1);
square_matrix = (original_data-mean_matrix_averaged).^2;
square_matrix(logical_pattern==0) = 0;

square_variance = sum(square_matrix)./sum(logical_pattern);
square_variance = square_variance.^0.5;

% mean_A = sum(A_all_segs)/total_count; %A平均值
% variance_A = A_all_segs-repmat(mean_A,total_count, 1);
% variance_A = variance_A.^2;
% variance_A = sum(variance_A) / total_count;
% 
% square_variance = variance_A.^0.5;
% mean_A_square = mean_A.^2;
sv = square_variance.^2;
mean_A_square = new_mean_value.^2;
X_A = sv./mean_A_square;
end

