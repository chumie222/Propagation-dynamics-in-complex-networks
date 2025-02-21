function [ gen, time ] = SteffA2(x0, tol)
%STEFF 此处显示有关此函数的摘要
%   此处显示详细说明
    if (nargin==1)
        tol=1.0e-5;
    end
    time = 0;
    wucha=0.1;
    gen = x0;
    while(wucha>tol)
       x1=gen;
       y=GA_thetaA(x1)+x1;
       z=GA_thetaA(y)+y;
       gen=x1-(y-x1)^2/(z-2*y+x1);
       wucha=abs(gen-x1);
       time=time+1;
    end
    gen;
    time;
end
