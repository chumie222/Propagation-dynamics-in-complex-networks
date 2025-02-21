function dy=th(t,y)

global lambda_A  r T_A rho_0 degree  degree_A  c k_A 
%   lambda_A为传播率，r_A为恢复概率，T为节点的固有阈值

%   y: theta_w_A(t)与theta_w_B(t)串连的向量


%网络A和网络B的平均度
avg_K_A=sum(degree_A(:,1).*degree_A(:,2));

theta_A=0;

len_degree_A = length(degree_A);


dy=zeros(len_degree_A,1);
%计算theta_A和theta_B
for w=1:len_degree_A
    theta_A=theta_A+(degree_A(w,1)*degree_A(w,2)/avg_K_A)*y(w);
end



%%计算每条边的感染概率
% lambda_w_A=zeros(length(weight_A),1);
% for w=1:len_weight_A
%     lambda_w_A(w)=1-(1-lambda_A)^weight_A(w,1);
% end
% 
% lambda_w_B=zeros(length(weight_B),1);
% for w=1:len_weight_B
%     lambda_w_B(w)=1-(1-lambda_B)^weight_B(w,1);
% end

%计算 xi_S_w_A
phi_1 = 0;
for k=1:length(degree_A)
    conservative = 0;
    
    temp_A=0;
    
    
	for a = 0:T_A-1
            if a<=degree_A(k,1)-1  
                temp_A = temp_A + nchoosek(degree_A(k,1)-1,a)* ...
                    (theta_A^(degree_A(k,1)-a-1))*...
                    (1-theta_A)^a;
            end
    end
    
    
    conservative=temp_A;
	phi_1 = phi_1 + degree_A(k,1) * degree_A(k,2) * conservative;
end
xi_S_w_A=phi_1*(1-rho_0)/avg_K_A;



%%计算xi_R_w_A
xi_R_w_A=zeros(len_degree_A,1);
for w=1:len_degree_A
    xi_R_w_A(w)=r*(1-y(w))*(degree_A(w,1)/(lambda_A*k_A(w))-1);
end


%计算 xi_I_W_A 
xi_I_W_A=zeros(len_degree_A,1);
for w=1:len_degree_A
    xi_I_W_A(w)=y(w)-xi_S_w_A-xi_R_w_A(w);
end


%写出微分方程
%计算dtheta_w_A_t
for w=1:len_degree_A
    dy(w)=-(lambda_A*k_A(w)/degree_A(w,1))*xi_I_W_A(w);
end
