clear all
clc;

% global lambda_A lambda_B r T_A T_B rho_0 degree q
% 
% %   y(1): theta(t)
% %   y(2): kesai_I^A(t)
% %   y(3): rho_I^A(t)
% %   y(4): r_A(t)
% 
% data=load('combined_degree.nw');
% max_degree=max(max(data(:,1)),max(data(:,2)));
% network_size=10000;
% 
% combined_degree = spconvert(data);
% combined_degree(max_degree,max_degree) = 0;
% combined_degree = full(combined_degree);
% 
% % for i=1:max_degree
% %     for j=1:max(data(:,2))
% %         count=count+1;
% %         degree=[degree;[i j 0]];
% %     end
% % end
% %  
% % for i=1:length(data)
% %     degree(conculate(data(i,1),data(i,2)),3)=degree(conculate(data(i,1),data(i,2)),3)+1;
% % end
% %  
% % degree(:,3)=degree(:,3)/network_size;
% 
% 
% start_value = 0;
% end_value = 1
% ER_3D_temp = [];
% for q=start_value:0.01:end_value
%     degree=[];
%     for i=1:max_degree
%        for j=1:max_degree
%            degree = [degree; [i,j,combined_degree(i,j)]];
%        end    
%     end
% 
%     temp=[];
%     for i=1:length(degree)
%         if degree(i,3)>0
%             temp=[temp;degree(i,:)];
%         end
%     end
%     degree=temp;
% 
% 
% 
%     r=1;
%     T_A=1;
%     T_B=3;
%     % rho_0=0.1;
%     % alpha=1;
% 
%     R=[];
% 
%     rho_0=0.0001;
%     temp_R=[];
%     for lambda_A=0.01:0.01:1
%         disp(['lambda_A is ' num2str(lambda_A) ', q is ' num2str(q)]);
%         lambda_B=lambda_A;
% 
%         [T1,F1]=ode45(@thresholdModel,[0:1:100],[1 0 1 0]);
% 
%         theta_A=F1(length(F1),1);
%         theta_B=F1(length(F1),3);
% 
%         s=0;
%         for kk=1:length(degree)
%             s=s+degree(kk,3)*susceptible_K(kk,theta_A,theta_B);
%         end
% 
%     %         dlmwrite('R_A=3,R_B=4.txt',1-s,'-append');
% 
%         temp_R=[temp_R 1-s]
%     end
%     R=[R;temp_R];
%     ER_3D_temp = [ER_3D_temp; [0, R]'];
% end
% file_name = sprintf('ER_3D_theoretical.txt');
% save(file_name,'ER_3D_temp','-ascii');
% subplot('position',[0.1,0.55,0.8,0.4]);
% all_result = load('ER_3D_theoretical.txt','-ascii');
% plot_3_data = [];
% temp = all_result;
% 
% for k=10:100
%    elements = temp(k*101+1:(k+1)*101);
%    diff_array = diff(elements)';
%    [value, index] = max(diff_array);
%    plot_3_data = [plot_3_data; [(index-1)*0.01, k*0.01, elements(index)]];
% end
% 
% total_data = reshape(all_result, 101, 101);
% [x,y] = meshgrid(0:0.01:1, 0:0.01:1);
% surf(x,y,total_data');
% hold on
% plot3(plot_3_data(:,1)', plot_3_data(:,2)', plot_3_data(:,3)', 'r-', 'LineWidth', 6);
% colorbar('location','EastOutside')
% % xlabel('\lambda');
% ylabel('q');
% shading interp;

% subplot('position',[0.1,0.1,0.8,0.4]);
all_result = load('er_R_q_lambda.txt','-ascii');  %er_R_q_lambda.txt
data = load('ER_X_A_.txt', '-ascii');

% for i=2
%     plot(0:0.01:1, data(i,:))
%     hold on
% end

plot_3_data = [];
temp = all_result(:,3);

first_data_set = [];
second_data_set1 = [];
second_data_set2 = [];

k_border = 15;
bias = 10;
for k=3:90
    exist_concave = 0;
    elements = data(k,2:end);
    diff_array = diff(elements);

    threshold = 0.001;
    peak_threshold = 0.01;
    max_add = 0;
    max_indax = 0;
    addition_value = 0;       
       
    if (k<k_border)
         %有两个峰
         for index=2:length(diff_array)-1
              if (diff_array(index-1)<0.001 && diff_array(index)>0.0001)   
                   exist_concave = 1;
                   addition_value = abs(diff_array(index-1))+abs(diff_array(index));
                   if ( addition_value > max_add)
                      max_add = addition_value;
                      max_indax = index;
                   end
              end  
         end
        [left_max, left_index] = max(elements(1:max_indax));
        second_data_set1 = [second_data_set1; [left_index*0.01, (k+bias)*0.01, left_max]];
        [right_max, right_index] = max(elements(max_indax+1:end));
        second_data_set2 = [second_data_set2; [(right_index+max_indax)*0.01, (k+bias)*0.01, right_max]];
    else
         %有一个峰
        [left_max, left_index] = max(elements);
        first_data_set = [first_data_set; [left_index*0.01, (k+bias)*0.01, left_max]];
    end     
end

%处理偏差较大的数据
second_data_set1([3,5,9,11],:) = [];
second_data_set1(4,2) = second_data_set1(4,2)-0.01;
second_data_set1(3,2) = second_data_set1(3,2)-0.005;
second_data_set1 = [second_data_set1; first_data_set(1,:)];
second_data_set2 = [second_data_set2; first_data_set(1,:)];

total_data = reshape(temp, 101, 101);
[x,y] = meshgrid(0:0.01:1, 0:0.01:1);
surf(x,y,total_data');
hold on
%画第一段
linewidth = 2;
markersize = 10;

plot3(first_data_set(:,1)', first_data_set(:,2)', ones(size(first_data_set(:,1)')), 'w-', 'LineWidth', linewidth);
hold on
plot3(first_data_set(1:4:end,1)', first_data_set(1:4:end,2)', ones(size(first_data_set(1:4:end,1)')), 'wo', 'markersize', markersize, 'LineWidth', 2);
hold on
% plot3(dash_line1(:,1)', dash_line1(:,2)', dash_line1(:,3)', 'm-.', 'LineWidth', linewidth);
plot3(second_data_set1(:,1)', second_data_set1(:,2)',ones(size(second_data_set1(:,1)')), 'g-', 'LineWidth', linewidth);
hold on
plot3(second_data_set1(1:end,1)', second_data_set1(1:end,2)', ones(size(second_data_set1(1:end,1)')), 'gs', 'markersize', markersize, 'LineWidth', 2);
hold on

plot3(second_data_set2(:,1)', second_data_set2(:,2)',ones(size(second_data_set2(:,1)')), 'r-', 'LineWidth', linewidth);
hold on
plot3(second_data_set2(1:end,1)', second_data_set2(1:end,2)', ones(size(second_data_set2(1:end,1)')), 'r^', 'markersize', markersize, 'LineWidth', 2);
hold on

%划边界
k=12;
plot3(0:0.01:1, k*0.01*ones(1,101), 10*ones(1,101), 'w--', 'LineWidth', linewidth);
hold on
%混合到二阶相变
k=25;
elements = temp(k*101+1:(k+1)*101);
plot3(0:0.01:1, k*0.01*ones(1,101), 10*ones(1,101), 'w-', 'LineWidth', linewidth);
hold on

colorbar('location','EastOutside')
xlabel('\lambda');
ylabel('q');
shading interp;

