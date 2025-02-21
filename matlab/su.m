function yy=su(kk,theta_A)

global T_A  rho_0 degree_A 
temp_A=0;

conservative = 0;
for m_A=0:T_A-1
        if m_A<=degree_A(kk,1) 
            temp_A=temp_A+...
                gamma(degree_A(kk,1)+1)/(gamma(degree_A(kk,1)+1-m_A)*gamma(m_A+1))*...
                theta_A^(degree_A(kk,1)-m_A)*...
                (1-theta_A)^(m_A);
        end 
end


conservative = temp_A;
yy=(1-rho_0)*conservative;