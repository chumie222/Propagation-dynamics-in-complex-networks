function [ gen, time ] = gexian( f, a, b, tol )
%GEXIAN 此处显示有关此函数的摘要
%   此处显示详细说明
    if (nargin==3)
       tol=1.0e-5; 
    end

    time=0;
    wucha=0.1;
    fa=subs(sym(f),a);
    fb=subs(sym(f),b);
    gen = a-(b-a)*fa/(fb-fa);
    %当误差大于给定的误差容限时候，进入循环
    while(wucha>tol)
       time=time+1;
       x1=gen;
       fx=subs(sym(f),x1);
       s=fx*fa;
       if (s>0)
           gen=b-(x1-b)*fb/(fx-fb);
       else
           gen=a-(x1-a)*fa/(fx-fa);
       end
       wucha=abs(gen-x1);
    end
end

