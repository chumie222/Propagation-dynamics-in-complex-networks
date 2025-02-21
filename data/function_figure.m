
x = 0:0.01 : 1;%%最低，步长，最高
%y = log(1 + x / 0.01) / log(1 + 1 / 0.01);

y = 0.1 * power(1 + 1 / 0.1, x) - 0.1;
figure %%新建一个幕布
plot(x, y)
title('h(x,b)')%%加上标题
xlabel('x')%%x标签
ylabel('p')%%y标签
xlim([0, 1])%%幕布x边缘范围，否则默认尾部留白
