function new_thetaA = GA_thetaA(thetaA)
%GA 此处显示有关此函数的摘要
%   此处显示详细说明
%   lambda_A为传播率，r_A为恢复概率，T为节点的固有阈值

%   y(1): theta_A(t)
%   y(2): xi_R_A(t)
%   y(3): theta_B(t)
%   y(4): xi_R_B(t)

%   degree=load('degree.txt');
%   网络A和网络B的平均度
global degree q lambda_A r T_A T_B rho_0 thetaB
    avg_K_A=sum(degree(:,1).*degree(:,3));

    %   计算xi_S_A
    phi_1 = 0;
    for k=1:length(degree)
        temp_A=0;
        temp_B=0;

        for a = 0:T_A-1
            if a<=degree(k,1)-1  
                temp_A = temp_A + nchoosek(degree(k,1)-1,a)* ...
                    (thetaA^(degree(k,1)-a-1))*...
                    (1-thetaA)^a;
            end
        end

        for b=0:T_B-1
            if b<=degree(k,2)
                temp_B = temp_B +...
                    nchoosek(degree(k,2),b)*...
                    (thetaB^(degree(k,2)-b))*...
                    (1-thetaB)^b;
            end 
        end
        active = temp_A*temp_B;
        conservative=1-(1-temp_A)*(1-temp_B);
        temp = q*active+(1-q)*conservative;
        phi_1 = phi_1 + degree(k,1) * degree(k,3) * temp;
    end
    xi_S_A=phi_1*(1-rho_0)/avg_K_A;
    tail = r*(1-lambda_A)*(1-thetaA)/lambda_A;
    new_thetaA = xi_S_A+tail-thetaA;
end

