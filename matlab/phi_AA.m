function y=phi_AA(k,theta)

global lambda_A lambda_B r T_A rho_0 degree

temp=0;
for a=0:T_A-1
    temp=temp+(1-rho_0)*nchoosek(k,a)*(theta^(k-a))*((1-theta)^a);
end
 
y=temp;