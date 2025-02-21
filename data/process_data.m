clc;
clear;
sf3_data = load('C_ori_b_lambda_rho0_0.001_b_0_right.txt','-ascii');
sfm_data = load('lambda_b_rho0_0.001_chazhi.txt','-ascii');
b = 5;
%每个结果做成一列，一共1000列
network_size = 10000;
total_count = 1000;
R3_infty = [];
index_vector = [ones(1,101)*(0.01*b); 0:0.01:1]';
for times=1:total_count
    R3_infty = [R3_infty; sf3_data((times-1)*5050+(b-1)*101+1:(times-1)*5050+b*101, 3)'];
end
R3_infty = R3_infty';

%计算每一行的平均值的一半
% mean_matrix = 50;
mean_value = sum(R3_infty,2)/(total_count*10);

%把每一行小于平均值一半的值变成0
mean_matrix = repmat(mean_value,1,total_count);
R3_infty(R3_infty<mean_matrix) = 0;
% mean_matrix = 50;
% R3_infty(R3_infty<mean_matrix) = 0;
%每一行求平均值
res = sum(R3_infty,2)./sum(R3_infty~=0,2);
logical_pattern = R3_infty~=0;
% res(1:49,:)=0;
res = res/network_size;
R3_infty = R3_infty/network_size;
mean_matrix_averaged = repmat(res,1,total_count);
square_matrix = (R3_infty-mean_matrix_averaged).^2;
square_matrix(logical_pattern==0) = 0;

square_variance = sum(square_matrix,2)./sum(logical_pattern,2);
square_variance = square_variance.^0.5;
% temp_vector = sf3_data((5-1)*101+1:5*101, 3);
% temp_vector(1:51,:) = 0;
% temp_vector(temp_vector<mean_matrix) = 0;
% res = temp_vector/10000;
res = [index_vector';res']';
square_variance = [index_vector';square_variance']';
save(['C_averaged_b_' num2str(b) '_lambda_b_rho0_0.001.txt'],'res','-ascii');
save(['C_averaged_b_' num2str(b) '_lambda_b_rho0_0.001_error.txt'],'square_variance','-ascii');
subplot(3,1,1);
plot(sfm_data((b-1)*101+1:b*101,2),sfm_data((b-1)*101+1:b*101,3),'g-');
% hold on
% errorbar(res(:,2),res(:,3),square_variance(:,3),'b');
hold on
plot(res(:,2),res(:,3),'bo');

subplot(3,1,2);
plot(square_variance(:,2),square_variance(:,3),'b');

subplot(3,1,3);
%计算以lambda为自变量，给定不同b下的波动值
%对应lambda的一行数据
VR_many_lambda_res = [];
for b_index = b
    VR_lambda_res = [];
    for lambda_index = 1:101
        R_line_duiyingB = [];
        for times = 1:total_count
            %找到给定b下的所有lambda以及对应的R值
            hang_index = (times-1)*5050+(b_index-1)*101+lambda_index;
            %把b对应的遍历lambda的一行值组织起来
            R_line_duiyingB = [R_line_duiyingB, sf3_data(hang_index,3)/network_size];
        end
        VR_lambda_res = [VR_lambda_res, variance_f(R_line_duiyingB)];
        clear R_line_duiyingB
    end
    plot(0:0.01:1, VR_lambda_res);
    hold on
    VR_many_lambda_res = [VR_many_lambda_res;VR_lambda_res];
    clear VR_lambda_res
end
VR_many_lambda_res = [0:0.01:1; VR_many_lambda_res];
VR_many_lambda_res = VR_many_lambda_res';
save('VR_lambda.txt','VR_many_lambda_res','-ascii');

