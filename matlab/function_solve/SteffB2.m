function [ gen, time ] = SteffB( x0)
%STEFFB 此处显示有关此函数的摘要
%   此处显示详细说明
    tol=1.0e-5;

    time = 0;
    wucha=0.1;
    gen = x0;
    while(wucha>tol)
       x1=gen;
       y=GB_thetaA(x1)+x1;
       z=GB_thetaA(y)+y;
       gen=x1-(y-x1)^2/(z-2*y+x1);
       wucha=abs(gen-x1);
       time=time+1;
    end
    gen;
    time;
end

