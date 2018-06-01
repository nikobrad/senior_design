function [d0,d1,d2,d3] = findDist(rot0,pos0,R)
%% findDist.m - find distance of each cable from motor to anchor point
% arguments: current rotation, position of payload, radius of shell
pi = 3.1415927;

pos = [pos0(1)*cos(pos0(2)-rot0),pos0(1)*sin(pos0(2)-rot0)];
a0 = [R*cos(rot0),R*sin(rot0)];
a1 = [R*cos(rot0+(pi/2)),R*sin(rot0+(pi/2))];
a2 = [R*cos(rot0+(pi)),R*sin(rot0+(pi))];
a3 = [R*cos(rot0+(3*pi/2)),R*sin(rot0+(3*pi/2))];

d0 = sqrt((a0(1)-pos(1))^2 + (a0(2)-pos(2))^2);
d1 = sqrt((a1(1)-pos(1))^2 + (a1(2)-pos(2))^2);
d2 = sqrt((a2(1)-pos(1))^2 + (a2(2)-pos(2))^2);
d3 = sqrt((a3(1)-pos(1))^2 + (a3(2)-pos(2))^2);