figure(1);
p1=plot(Normal(:,1),Normal(:,2:5));
set(p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Normal Forces [N]')
legend('Rear Bogie Front Rigth Wheel','Rear Bogie Rear Rigth Wheel','Front Bogie Front Rigth Wheel','Front Bogie Rear Rigth Wheel')
print -dpng 2Dnormal.png
saveas(gcf,'2Dnormal.fig');

figure(2);
p1=plot(SLIP(:,1),SLIP(:,2:5));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Slip Velocity [m/s]')
legend('Rear Bogie Front Rigth Wheel','Rear Bogie Rear Rigth Wheel','Front Bogie Front Rigth Wheel','Front Bogie Rear Rigth Wheel')
print -dpng 2Dslip.png
saveas(gcf,'2Dslip.fig');

figure(3);
p1=plot(xWAG(:,1),xWAG(:,2));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('XWAG [m]')
legend('Wagon x position')
print -dpng 2DxWAG.png
saveas(gcf,'2DxWAG.fig');

figure(4);
p1=plot(ddxWAG(:,1),ddxWAG(:,2));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('ddXWAG [m]')
legend('Wagon x acceleration')
print -dpng 2DddxWAG.png
saveas(gcf,'2DddxWAG.fig');

figure(5);
p1=plot(Nu(:,1),Nu(:,2:5));
set (p1, 'linewidth', 2) 
set(gca,'FontSize',20)
xlabel('Time [s]')
ylabel('Coefficient of friction')
legend('Rear Bogie Front Rigth Wheel','Rear Bogie Rear Rigth Wheel','Front Bogie Front Rigth Wheel','Front Bogie Rear Rigth Wheel')
print -dpng 2Dnu.png
saveas(gcf,'2Dnu.fig');