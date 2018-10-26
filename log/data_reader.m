clc;clear;close all;
% 364.35 mGauss ?????
N = 1;
S = 1000;
E = 1;
fs = 1000;
x_freq = 70;
y_freq = 80;
z_freq = 60;
fileID = fopen('Line test/high_carbon_50Hz_25Hz_10Hz_10Vpp.log','r');
formatSpec = '%c %d %d %d %d:%d:%d\r\n';
sizeData = [7 Inf];
data = fscanf(fileID, formatSpec, sizeData);
fclose(fileID);
data = data';
data(:,2:4) = data(:,2:4)./6842;
[r_data, c_data] = find(data(:,1)==77);
% data(r_data,:) = [];
data = data(r_data,:);
L = size(data,1);
max = max(data(:,2:4));
min = min(data(:,2:4));
% data(:,2:4) = data(:,2:4)-((max-min)./2+min);
plot((N:S)/fs,data(N:S,2:4))
legend('x','y','z')
data_freq = fft(data(:,2:4));
% x_mag_dir = (abs(data_freq(L/fs*x_freq,:))+abs(data_freq(L/fs*(fs-x_freq),:)))/fs;
% y_mag_dir = (abs(data_freq(L/fs*y_freq,:))+abs(data_freq(L/fs*(fs-y_freq),:)))/fs;
% z_mag_dir = (abs(data_freq(L/fs*z_freq,:))+abs(data_freq(L/fs*(fs-z_freq),:)))/fs;
% figure
% quiver3(zeros(1,1),zeros(1,1),zeros(1,1),x_mag_dir(1),x_mag_dir(2),x_mag_dir(3)); hold on;
% quiver3(zeros(1,1),zeros(1,1),zeros(1,1),y_mag_dir(1),y_mag_dir(2),y_mag_dir(3)); 
% quiver3(zeros(1,1),zeros(1,1),zeros(1,1),z_mag_dir(1),z_mag_dir(2),z_mag_dir(3)); 
% quiver3(0,0,0,1,0,0);
% quiver3(0,0,0,0,1,0);
% quiver3(0,0,0,0,0,1);
% legend('x mag dir','y mag dir','z mag dir','x','y','z')
% hold off
figure
plot((0:1/L:1-1/L)*fs,abs(data_freq(1:end,:)/L))
legend('x','y','z')

figure
plot((1:size(data,1))/fs,data(:,2:4))
legend('x','y','z')

% =====================================================================
