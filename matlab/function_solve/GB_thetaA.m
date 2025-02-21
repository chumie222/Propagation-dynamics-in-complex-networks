function new_thetaA = GB_thetaA(thetaA)
%GB 此处显示有关此函数的摘要
%   此处显示详细说明
global degree q lambda_B r T_A T_B rho_0 thetaB
    avg_K_B=sum(degree(:,2).*degree(:,3));
    phi_1 = 0;
    for k=1:length(degree)
        temp_A=0;
        temp_B=0;

        for a = 0:T_B-1 
            if a<=degree(k,2)-1  
                temp_B = temp_B + nchoosek(degree(k,2)-1,a)* ...
                    (thetaB^(degree(k,2)-a-1))*...
                    (1-thetaB)^a ;
            end
        end

        for  b=0:T_A-1
            if b<=degree(k,1)
                temp_A = temp_A +  ...
                    nchoosek(degree(k,1),b)*...
                    (thetaA^(degree(k,1)-b))*...
                    (1-thetaA)^b;
            end 
        end

        active = temp_A*temp_B;
        conservative=1-(1-temp_A)*(1-temp_B);
        temp=q*active+(1-q)*conservative;
        phi_1 = phi_1 + degree(k,2) * degree(k,3) * temp;
    end
    xi_S_B=phi_1*(1-rho_0)/avg_K_B;
    tail = r*(1-lambda_B)*(1-thetaB)/lambda_B;
    new_thetaA = xi_S_B+tail-thetaA;
end

