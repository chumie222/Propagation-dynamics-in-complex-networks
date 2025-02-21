function thetaA = f_A(lambda_A, lambda_B, r, T_A, T_B, rho_0, degree, q, thetaB)
%F_U Summary of this function goes here
%   Detailed explanation goes here
      thetaA = 1;
   
      while 1
          old_thetaA = thetaA;
          tail = r*(1-lambda_A)*(1-thetaA)/lambda_A;

          thetaA = GA(lambda_A, lambda_B, r, T_A, T_B, rho_0, degree, q, thetaA, thetaB)
          
          if abs(old_thetaA-thetaA) < 10^-3
             break;
          elseif thetaA>1
             break;
          end
          
%           if isnan(thetaA)
%               thetaA = 0;
%           end
      end
end

