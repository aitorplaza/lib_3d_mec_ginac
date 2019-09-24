figure(1);
p1=plot(Normal(:,1),Normal(:,2:9));
set(p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Normal Forces [N]')
legend('Front Bogie Front Rigth Wheel','Front Bogie Front Left Wheel','Front Bogie Rear Rigth Wheel','Front Bogie Rear Left Wheel','Rear Bogie Front Rigth Wheel','Rear Bogie Front Left Wheel','Rear Bogie Rear Rigth Wheel','Rear Bogie Rear Left Wheel')
print -dpng 3Dnormal2.png
saveas(gcf,'3Dnormal2.fig');

figure(2);
p1=plot(SLIP(:,1),SLIP(:,2:9));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Slip Velocity [m/s]')
legend('Front Bogie Front Rigth Wheel','Front Bogie Front Left Wheel','Front Bogie Rear Rigth Wheel','Front Bogie Rear Left Wheel','Rear Bogie Front Rigth Wheel','Rear Bogie Front Left Wheel','Rear Bogie Rear Rigth Wheel','Rear Bogie Rear Left Wheel')
print -dpng 3Dslip2.png
saveas(gcf,'3Dslip2.fig');

figure(3);
p1=plot(xWAG(:,1),xWAG(:,2));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('XWAG [m]')
legend('Wagon x position')
print -dpng 3DxWAG2.png
saveas(gcf,'3DxWAG2.fig');

figure(4);
p1=plot(ddxWAG(:,1),ddxWAG(:,2));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('ddXWAG [m]')
legend('Wagon x acceleration')
print -dpng 3DddxWAG2.png
saveas(gcf,'3DddxWAG2.fig');

figure(5);
p1=plot(Nu(:,1),Nu(:,2:9));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Coefficient of friction')
legend('Front Bogie Front Rigth Wheel','Front Bogie Front Left Wheel','Front Bogie Rear Rigth Wheel','Front Bogie Rear Left Wheel','Rear Bogie Front Rigth Wheel','Rear Bogie Front Left Wheel','Rear Bogie Rear Rigth Wheel','Rear Bogie Rear Left Wheel')
print -dpng 3Dnu2.png
saveas(gcf,'3Dnu2.fig');