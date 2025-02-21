function yy=susceptible_K(kk,theta_A,theta_B)

global  rho_0 degree a b  

temp_A=0;
temp_B=0;

for m_A=0:degree(kk,1)-1
        cond_A = 1;        
            for j=0:m_A
                cond_A = cond_A*(1-cusp_condition_A(j/degree(kk,1),a)); 
            end 
            temp_A=temp_A+...
                gamma(degree(kk,1)+1)/(gamma(degree(kk,1)+1-m_A)*gamma(m_A+1))*...
                theta_A^(degree(kk,1)-m_A)*...
                (1-theta_A)^(m_A)*cond_A;
end

for m_B=0:degree(kk,2)-1
         cond_B = 1;
            for j=0:m_B   
                cond_B = cond_B*(1-cusp_condition_B(j/degree(kk,2),a,b)); 
            end
            temp_B=temp_B+...
                gamma(degree(kk,2)+1)/(gamma(degree(kk,2)+1-m_B)*gamma(m_B+1))*...
                theta_B^(degree(kk,2)-m_B)*...
                (1-theta_B)^(m_B)*cond_B;
end

conservative = temp_A*temp_B;
yy=conservative*(1-rho_0);
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