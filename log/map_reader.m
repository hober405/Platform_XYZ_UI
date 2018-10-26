% clc;clear;close all;
% 364.35 mGauss ?????
clc;clear;close all
fileID = fopen('Motor_log Mon Jul 2 2018.log','r');
formatSpec = '%c %d %d %d %d:%d:%d\r\n';
sizeData = [7 Inf];
data = fscanf(fileID, formatSpec, sizeData);
fclose(fileID);
data = data';
pos_mag = [];
total_index = 1;
mag_tmp = [];
index = 1;
pos_mag(total_index,1:3) = data(1,2:4);
for i=1:size(data,1)
    if (data(i,1)== 79) && ~isequal(pos_mag(total_index,1:3), data(i,2:4))
        pos_mag(total_index,4:6) = mean(mag_tmp);
        total_index = total_index + 1;
        pos_mag(total_index,1:3) = data(i,2:4);
        index = 1;
    elseif data(i,1) == 77
        mag_tmp(index,1:3) = data(i,2:4)./6842;
        index = index+1;
    end
end
pos_mag(total_index,4:6) = mean(mag_tmp);

% 
% fileLand = fopen('ground_cube20180608.log','r');
% ground = fscanf(fileLand, formatSpec, sizeData);
% fclose(fileLand);
% ground = ground';
% pos_ground = [];
% mag_tmp = [];
% total_index = 1;
% index = 1;
% pos_ground(total_index,1:3) = ground(1,2:4);
% for i=1:size(ground,1)
%     if (ground(i,1)== 79) && ~isequal(pos_ground(total_index,1:3), ground(i,2:4))
%         pos_ground(total_index,4:6) = mean(mag_tmp);
%         total_index = total_index + 1;
%         pos_ground(total_index,1:3) = ground(i,2:4);
%         index = 1;
%     elseif ground(i,1) == 77
%         mag_tmp(index,1:3) = ground(i,2:4)./6842;
%         index = index+1;
%     end
% end
% pos_ground(total_index,4:6) = mean(mag_tmp);
figure
% quiver3(pos_mag(:,1),pos_mag(:,2),pos_mag(:,3),pos_mag(:,4),pos_mag(:,5),pos_mag(:,6),5); hold on;
scatter3(pos_mag(:,1),pos_mag(:,2),pos_mag(:,3),'.');
% quiver3(175,207,-5,1,0,0,5);
% quiver3(175,207,-5,0,1,0,5);
% quiver3(175,207,-5,0,0,1,5);
% axis([170,210,202,242,-0,20])
% legend('x mag dir','y mag dir','z mag dir','x','y','z')
hold off
title('Over all')
% pos_mag(:,4:6) = pos_mag(:,4:6) - pos_ground(:,4:6);
% 
% figure
% quiver3(pos_mag(:,1),pos_mag(:,2),pos_mag(:,3),pos_mag(:,4),pos_mag(:,5),pos_mag(:,6),5); hold on;
% % % quiver3(175,207,-5,1,0,0,5);
% % % quiver3(175,207,-5,0,1,0,5);
% % % quiver3(175,207,-5,0,0,1,5);
% % % axis([170,210,202,242,-0,20])
% % % legend('x mag dir','y mag dir','z mag dir','x','y','z')
% hold off
% 
% title('mag');
% figure
% quiver3(pos_ground(:,1),pos_ground(:,2),pos_ground(:,3),pos_ground(:,4),pos_ground(:,5),pos_ground(:,6),5); hold on;
% % % quiver3(175,207,-5,1,0,0,5);
% % % quiver3(175,207,-5,0,1,0,5);
% % % quiver3(175,207,-5,0,0,1,5);
% % % axis([170,210,202,242,-0,20])
% % % legend('x mag dir','y mag dir','z mag dir','x','y','z')
% hold off
% title('ground')