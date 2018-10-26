% clc;clear;close all;
% 364.35 mGauss ?????
function [pos_mag]=map_reader(fileName,draw_or_not)
fileID = fopen(fileName,'r');
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
if draw_or_not,
figure
quiver3(pos_mag(:,1),pos_mag(:,2),pos_mag(:,3),pos_mag(:,4),pos_mag(:,5),pos_mag(:,6),5); hold on;
hold off
title(fileName)
end