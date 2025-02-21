clc;
clear;

q=0.1;
lambda_A=0.95;

file_name = sprintf("thetaB_thetaA_lambda2_%.3f_q_%.3f.nw", lambda_A, q);
theta_B=load(file_name, '-ascii');
plot(theta_B(:,2)', theta_B(:,1)','b-', 'LineWidth',3);
hold on
file_name = sprintf("thetaA_thetaB_lambda1_%.3f_q_%.3f.nw", lambda_A, q);
theta_A=load(file_name, '-ascii');
plot(theta_A(:,1)', theta_A(:,2)','r-.', 'LineWidth',3);

% if (q==0.2)
%     if(lambda_A==0.47 || lambda_A==0.59)
%         hold on
%         file_name = sprintf("thetaB_thetaA_lambda2_%.2f_q_%.2f_dot.nw", lambda_A, q);
%         theta_B=load(file_name, '-ascii');
%         plot(theta_B(:,2)', theta_B(:,1)','o','Color',[1 0 0],'MarkerSize',15);
%     end
% end
% hold on
% file_name = sprintf("thetaB_thetaA_lambda2_%.3f_q_%.2f_dot.nw", lambda_A, q);
% theta_B=load(file_name, '-ascii');
% plot(theta_B(:,2)', theta_B(:,1)','o','Color',[1 0 0],'MarkerSize',15);
% xlabel('\theta_A')
% ylabel('\theta_B')
axis([0,1,0,1])
set(gca,'XTick',[0:0.5:1]) 
set(gca,'YTick',[0:0.5:1]) 
set(gca,'FontName','Times New Roman', 'FontSize', 40);