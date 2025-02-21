function dy=thresholdModel(t,y)

global lambda_A lambda_B r_A r_B rho_0 degree degree_A degree_B a b
%   lambda_A为传播率，r_A为恢复概率，T为节点的固有阈值

%   y: theta_w_A(t)与theta_w_B(t)串连的向量


%网络A和网络B的平均度
avg_K_A=sum(degree_A(:,1).*degree_A(:,2));
avg_K_B=sum(degree_B(:,1).*degree_B(:,2));


theta_A=0;
theta_B=0;
%len_degree_A = length(degree_A);
%len_degree_B = length(degree_B);
len_degree = length(degree);
dy=zeros(len_degree+len_degree,1);
%计算theta_A和theta_B
for w=1:len_degree
    theta_A=theta_A+(degree(w,1)*degree(w,3)/avg_K_A)*y(w);
end
%计算theta_B
for w=1:len_degree
    theta_B=theta_B+(degree(w,2)*degree(w,3)/avg_K_B)*y(w+len_degree);
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

inf_w_A=zeros(len_degree,1);
for w=1:len_degree
    inf_w_A(w)=lambda_A;
end
inf_w_B=zeros(len_degree,1);
for w=1:len_degree
    inf_w_B(w)=lambda_B;
end


%计算 xi_S_w_A

    for w=1:len_degree
   
    temp_A=0;
    temp_B=0;
	  for m_a = 0:degree(w,1)-1  %#ok<ALIGN>
        cond_A = 1;   
            for j=1:m_a
                cond_A = cond_A*(1-cusp_condition_A(j/degree(w,1), a)); 
            end      
                temp_A = temp_A + (gamma(degree(w,1))/(gamma(m_a+1)*gamma(degree(w,1)-1-m_a+1)))* ...
                (theta_A^(degree(w,1)-m_a-1))*...
                (1-theta_A)^m_a*cond_A;
      end
      
      for m_b=0:degree(w,2)
          cond_B = 1;
            for j=1:m_b
                cond_B = cond_B*(1-cusp_condition_B(j/degree(w,2),a,b)); 
            end
                temp_B = temp_B + (gamma(degree(w,2)+1)/(gamma(m_b+1)*gamma(degree(w,2)-m_b+1)))* ...
                 (theta_B^(degree(w,2)-m_b))*...
                 (1-theta_B)^m_b*cond_B; 
      
      end
     xi_S_w_A(w)=temp_A*temp_B*(1-rho_0); 
    end 



%计算 xi_S_w_B
    
    for w=1:len_degree
         temp_A=0;
         temp_B=0;
         for m_a = 0:degree(w,2)-1
            cond_A = 1;   
            for j=1:m_a
                cond_A = cond_A*(1-cusp_condition_B(j/degree(w,2),a,b)); 
            end
                temp_B =temp_B + (gamma(degree(w,2))/(gamma(m_a+1)*gamma(degree(w,2)-1-m_a+1)))* ...
                (theta_B^(degree(w,2)-m_a-1))*...
                (1-theta_B)^m_a*cond_A;
            
          end

    for  m_b=0:degree(w,1)
          cond_B = 1;
            for j=1:m_b
                cond_B = cond_B*(1-cusp_condition_A(j/degree(w,1),a)); 
            end  
                temp_A = temp_A + (gamma(degree(w,1)+1)/(gamma(m_b+1)*gamma(degree(w,1)-m_b+1)))* ...
                (theta_A^(degree(w,1)-m_b))*...
                (1-theta_A)^m_b*cond_B; 
    end
     xi_S_w_B(w)=temp_A*temp_B*(1-rho_0);
    end
  

%%计算xi_R_w_A
xi_R_w_A=zeros(len_degree,1);
for w=1:len_degree
    xi_R_w_A(w)=r_A*(1-y(w))*(1-inf_w_A(w))/inf_w_A(w);
end

%%计算xi_R_w_B
xi_R_w_B=zeros(len_degree,1);
for w=1:len_degree
    xi_R_w_B(w)=r_B*(1-y(w+len_degree))*(1-inf_w_B(w))/inf_w_B(w);
end

%计算 xi_I_W_A 
xi_I_W_A=zeros(len_degree,1);
for w=1:len_degree
    xi_I_W_A(w)=y(w)-xi_S_w_A(w)-xi_R_w_A(w);
end

%计算 xi_I_W_B
xi_I_W_B=zeros(len_degree,1);
for w=1:len_degree
    xi_I_W_B(w)=y(w+len_degree)-xi_S_w_B(w)-xi_R_w_B(w);
end

%写出微分方程
%计算dtheta_w_A_t
for w=1:len_degree
    dy(w)=-inf_w_A(w)*xi_I_W_A(w);
end

%计算dtheta_w_B_t
for w=1:len_degree
    dy(w+len_degree)=-inf_w_B(w)*xi_I_W_B(w);
end
end

function prob_A = cusp_condition_A(inst_rate, a)
    if (0<inst_rate && inst_rate<=a)
        prob_A = 1;
    elseif (a<inst_rate && inst_rate<=1)
        prob_A = 0;
    else
        prob_A = 0;
    end
end

function prob_B = cusp_condition_B(inst_rate, a, b)
    if (0<inst_rate && inst_rate<a-b)
        prob_B = 0;
    elseif (a-b<=inst_rate && inst_rate<=1)
        prob_B = 1;
    else
        prob_B = 0;
    end
end