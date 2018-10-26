clc;clear;close all

%% collect data
% 364.35 mGauss ?????
str.pre = 'T_shape_';
str.x = 'x_';
str.y = 'y_';
str.g = 'ground';
str.m = 'mag';
str.end = '.log';
files = {   [str.pre,str.x,str.g,str.end], ...
            [str.pre,str.y,str.g,str.end], ...
            [str.pre,str.x,str.m,str.end], ...
            [str.pre,str.y,str.m,str.end] };
data = cell(4);
pos_center = [212;231;37];
mag_pos = [216;227;-34];
H = [-0.4;0;-1]; 
H = H/sum(H.^2);

for i = 1:4
    data{i} = map_reader(files{i},0);
end

pos_x = data{1}(:,1:3);
pos_y = data{2}(:,1:3);
pos = [pos_x;pos_y];
pos_center = pos(1,1:3);
r_center = pos_center'-mag_pos;
mag_x = data{3}(:,4:6)-data{1}(:,4:6);
mag_y = data{4}(:,4:6)-data{2}(:,4:6);
mag = [mag_x;mag_y];
mag_center = mag(1,1:3);
r_center_s = sum(r_center.^2)^0.5;
Bt = sum(mag_center.^2)'./sum((3*(r_center)'*H*r_center./r_center_s^5-H/r_center_s^3).^2);
Bt = Bt^0.5
Bt_3 = mag_center'./((3*(r_center)'*H*r_center-H)/sum(r_center.^2)^(3/2));
r = pos'-repmat(mag_pos,1,size(pos,1));
r_s = sum(r.^2).^0.5;
predict_B = Bt*(3*H'*r.*r./r_s.^5-H./r_s.^3);
r_scalar = sum(r.^2).^0.5;
B_scalar = sum(predict_B.^2).^0.5;
mag_scalar = sum(mag'.^2).^0.5;
figure
quiver3(pos(:,1),pos(:,2),pos(:,3),mag(:,1),mag(:,2),mag(:,3),0.5);hold on
quiver3(pos(:,1),pos(:,2),pos(:,3),predict_B(1,:)',predict_B(2,:)',predict_B(3,:)',0.5);hold on
figure
plot(r_scalar, mag_scalar, 'x'); hold on;
plot(r_scalar, B_scalar, 'x');
legend('mag','predict');
axis equal;
% quiver3(pos_center(:,1),pos_center(:,2),pos_center(:,3),mag_center(:,1),mag_center(:,2),mag_center(:,3),5,'r');