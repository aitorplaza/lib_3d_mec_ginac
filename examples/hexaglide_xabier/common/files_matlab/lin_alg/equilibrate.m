function [Weq,c,r]=equilibrate(W)

c=max(abs(W));
for j=1:length(c)
	Waux(:,j)=c(j)^-1*W(:,j);
end

Waux2=Waux';
r=max(abs(Waux2));
for i=1:length(r)
	Waux3(:,i)=r(i)^-1*Waux2(:,i);
end
Weq=Waux3';
