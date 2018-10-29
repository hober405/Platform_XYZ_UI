clc;clear;close all;
% 364.35 mGauss ?????

%% for calibration
cal = 1;
filename = 'pololu5mag_cal_earth_1.log';  savename = ['tmp.mat'];


%% for evaluation
alpha = 0.7;
center = 4;
N = 1;
S = 1000;
E = 0;
fs = 1000;
% dir = 'pos_153_228_30';
% dir = 'pos_173_228_40';
% dir = 'pos_113_168_0';
% cal = 0;
% filename = [dir '\pololu5mag_x_axis_magnet.log'];  savename = [dir '/pololu_x_axis_magnet.mat'];
% filename = [dir '\pololu5mag_y_axis_magnet.log'];  savename = [dir '/pololu_y_axis_magnet.mat'];
% filename = [dir '\pololu5mag_z_axis_magnet.log'];  savename = [dir '/pololu_z_axis_magnet.mat'];
formatSpec = '%s %d %d %d %d:%d:%d\r\n';
sizeData = [8 Inf];
fileID = fopen(filename,'r');
data = fscanf(fileID, formatSpec, sizeData);
fclose(fileID);
data = data';
data(:,2) = data(:,2)-'0';
U = zeros(3,3,5);
c = zeros(3,5);
mag_data = cell(5);
rot = zeros(3,3,5);
data(:,3:5) = data(:,3:5)./6842.0;
if cal==1
    for magneto=1:5
        [r_data, c_data] = find(data(:,2)==magneto);
        % data(r_data,:) = [];
        raw_data = data(r_data(N:end-E),3:5);
        figure
        plot3(raw_data(:,1),raw_data(:,2),raw_data(:,3)); hold on
        axis equal
        axis([-1.2,1.2,-1.2,1.2,-1.2,1.2])
        grid on
        title('visualize raw')
%         raw_data = (1-alpha)*raw_data(1:end-1,:)+alpha*raw_data(2:end,:);
        L = size(raw_data,1);
        [U(:,:,magneto),c(:,magneto)]=MgnCalibration(raw_data);
        % max_data = max(raw_data(:,2:4));
        % min_data = min(raw_data(:,2:4));
        % scale_data = max_data-min_data;
        raw_data = (U(:,:,magneto)*(raw_data'-repmat(c(:,magneto),1,L)))';
        mag_data{magneto} = raw_data';
        % vec_length = sum(raw_data'.^2).^0.5;
        % figure
        % plot((1:size(raw_data,1))/fs,vec_length)
        % raw_data = (raw_data'./sum(raw_data'.^2).^0.5)';
        % % figure
        % % plot((N:S)/fs,raw_data(N:S,2:4))
        % % legend('x','y','z')
        % % data_freq = fft(raw_data(:,2:4));
        % % x_mag_dir = (abs(data_freq(L/fs*x_freq,:))+abs(data_freq(L/fs*(fs-x_freq),:)))/fs;
        % % y_mag_dir = (abs(data_freq(L/fs*y_freq,:))+abs(data_freq(L/fs*(fs-y_freq),:)))/fs;
        % % z_mag_dir = (abs(data_freq(L/fs*z_freq,:))+abs(data_freq(L/fs*(fs-z_freq),:)))/fs;
        % % figure
        % % quiver3(zeros(1,1),zeros(1,1),zeros(1,1),x_mag_dir(1),x_mag_dir(2),x_mag_dir(3)); hold on;
        % % quiver3(zeros(1,1),zeros(1,1),zeros(1,1),y_mag_dir(1),y_mag_dir(2),y_mag_dir(3));
        % % quiver3(zeros(1,1),zeros(1,1),zeros(1,1),z_mag_dir(1),z_mag_dir(2),z_mag_dir(3));
        % % quiver3(0,0,0,1,0,0);
        % % quiver3(0,0,0,0,1,0);
        % % quiver3(0,0,0,0,0,1);
        % % legend('x mag dir','y mag dir','z mag dir','x','y','z')
        % % hold off
        % % figure
        % % plot((0:1/L:1-1/L)*fs,abs(data_freq(1:end,:)/L))
        % % legend('x','y','z')
        %
        figure
        plot((1:size(raw_data,1))/fs,raw_data)
        legend('x','y','z')
        %
        % figure(103)
        % scatter3(raw_data(:,2),raw_data(:,3),raw_data(:,4),'.'); hold on
        % axis equal
        % title('visualize')
        
        % =====================================================================
        i=200;
        figure(101)
        quiver3(0,0,0,raw_data(i,1),raw_data(i,2),raw_data(i,3)); hold on
        title('Earth Magnetic')
        axis equal
    end
    R = zeros(3,3,5);
    for magneto=1:5
        mag_mag = mag_data{magneto}./sum(mag_data{magneto}.^2).^0.5;
        mag_cen = mag_data{center}./sum(mag_data{center}.^2).^0.5;
        rot(:,:,magneto) = mag_cen*mag_mag'*(mag_mag*mag_mag')^-1;
        [rot(:,:,magneto),R(:,:,magneto)] = qr(rot(:,:,magneto));
        rot(:,:,magneto) = rot(:,:,magneto).*sign(diag(R(:,:,magneto)));
        rot_inv = rot(:,:,magneto)^-1;
        mag = rot(:,:,magneto)*mag_data{magneto};
        figure
        plot3(mag(1,:),mag(2,:),mag(3,:)); hold on
        axis equal
        axis([-1.2,1.2,-1.2,1.2,-1.2,1.2])
        grid on
        title('visualize rot')
        
        figure(106)
        quiver3(0,0,0,mag(1,i),mag(2,i),mag(3,i)); hold on
        axis equal
        title('Earth Magnetic rot')
        
        figure(107)
        quiver3(zeros(3,1),zeros(3,1),zeros(3,1),...
            rot_inv(:,1),rot_inv(:,2),rot_inv(:,3)); hold on
        axis equal
        title('rot')
    end
    save('pololu_cal_data.mat','U','c','rot');
else
%     mag_data = zeros(3,5);
    mag_data = cell(1,5);
    for magneto=1:5
        load('pololu_cal_data.mat');
        [r_data, c_data] = find(sum(data(:,1:2)==['M',magneto],2)==2);
        % data(r_data,:) = [];
        raw_data = data(r_data(N:end-E),3:5);
        raw_data = (1-alpha)*raw_data(1:end-1,:)+alpha*raw_data(2,end,:);
        L = size(raw_data,1);
        
        %         raw_data =  (U(:,:,magneto)*(raw_data'-repmat(c(:,magneto),1,L)))';
        figure
        plot((1:size(raw_data,1))/fs,raw_data)
        legend('x','y','z')
        axis([-inf,inf,-3,3])
        
        mean_raw = mean(raw_data);
        for xyz=1:3
            low_mean_idx = (raw_data(:,xyz) < mean_raw(xyz));
            low_sum = sum(low_mean_idx);
            if abs((max(sum(low_mean_idx),sum(~low_mean_idx))/min(sum(low_mean_idx),sum(~low_mean_idx)))-2) < 0.3
                break;
            end
        end
        if low_sum < size(raw_data,1)/2
            earth_data = raw_data(~low_mean_idx,:);
            mix_data = raw_data(low_mean_idx,:);
        else
            earth_data = raw_data(low_mean_idx,:);
            mix_data = raw_data(~low_mean_idx,:);
        end
        earth_data_mean = mean(earth_data);
        earth_data_mean_total(magneto,:) = earth_data_mean;
        figure(101)
        quiver3(0,0,0,earth_data_mean(1),earth_data_mean(2),earth_data_mean(3)); hold on
        title('Earth Magnetic')
        mag_data{magneto} = raw_data-mean(earth_data);
        mag_data{magneto} = (U(:,:,magneto)*(mag_data{magneto}'))';
        disp(max(sum(low_mean_idx),sum(~low_mean_idx))/min(sum(low_mean_idx),sum(~low_mean_idx)))
        
        figure(100)
        scatter3(...zeros(L,1),zeros(L,1),zeros(L,1),
            mag_data{magneto}(:,1),mag_data{magneto}(:,2),mag_data{magneto}(:,3)); hold on
        title('Magnet magnetic data')
        xlabel('X');
        ylabel('Y')
        zlabel('Z')
        axis equal
    end
    save(savename,'mag_data');
end