function yy=conculate(x,y)
global degree 
%%计算度为x,y的编号

temp=0;
for i=1:x-1
    for j=1:max(degree(:,2))
        temp=temp+1;
    end
end

yy=temp+y;