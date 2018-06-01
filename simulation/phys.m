function [velocity,rotation] = phys (vel0,rot0,pos0,m,M,R,t)
%% phys.m - find velocity and rotation of robot after one tick of time
% arguments: current rotational velocity, current rotation, current payload position
% (polar), mass of payload, mass of rest of robot, radius of outer shell,
% length per tick of time
torque = pos0(1)*9.8*m*cos(pos0(2)-rot0);
rotAccel = M/torque;
velocity(1) = vel0 + (rotAccel*t);
velocity(2) = velocity(1)*R;
rotation = velocity*t;
