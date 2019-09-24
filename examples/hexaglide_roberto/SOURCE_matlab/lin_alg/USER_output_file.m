%% Output data for Hexaglide
output_format='%.6f\t %.10f\t %.10f\t %.10f\t %.10f\t %.10f\t \n';
output_data=[q_all(:,19),q_all(:,1),q_all(:,21),dq_all(:,1),dq_all(:,21)];

%% Output data for Train_proto
%output_format='%.6f\t %.10f\t %.10f\t %.10f\t %.10f\t \n';
%output_data=[q_all(:,1),q_all(:,2),dq_all(:,1),dq_all(:,2)];

%% Standard output file for any output_format and output_data
fi=fopen(name,'w');   
for i=1:n_points;
    fprintf(fi,output_format,t_all(i),output_data(i,:));
end
fclose('all');
%clear t_all, q_all, dq_all, output_data;