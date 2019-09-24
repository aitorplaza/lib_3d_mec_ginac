function v=complementary(jb,n);

jb=sort(jb,'ascend');

j=1;
k=1;
for i=1:n
	if length(jb)>=j & jb(j)==i
		j=j+1;
	else
		v(k)=i;
		k=k+1;
	end
end