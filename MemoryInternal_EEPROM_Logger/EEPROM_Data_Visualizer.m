%Load EEPROM data file
data=load('data.asc');

%data loaded, classifying variables
t=data(:,1);
h=data(:,2);

%plots
figure;
plot(t,'r','LineWidth',5);
title('Temperature');
ylim([0 50]);
xlim([0 size(t,1)]);

figure;
plot(h,'b','LineWidth',5);
title('Humidity');
ylim([10 90]);
xlim([0 size(t,1)]);
