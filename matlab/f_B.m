function thetaB = f_B(lambda_A, lambda_B, r, T_A, T_B, rho_0, degree, q, thetaA)
%F_U Summary of this function goes here
%   Detailed explanation goes here
      thetaB = 1;
      while 1
          old_thetaB = thetaB;
          tail = r*(1-lambda_B)*(1-thetaB)/lambda_B;
          thetaB = GB(lambda_A, lambda_B, r, T_A, T_B, rho_0, degree, q, thetaA, thetaB)
          if abs(old_thetaB-thetaB) < 10^-3
             break;
          elseif thetaB>1
             break;
          end
          
%           if isnan(thetaB)
%               thetaB = 0;
%           end
      end
end

