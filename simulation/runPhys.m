clear all
close all
clc

R = 10;
m = 5;
M = 5;
pi = 3.1415927;
pos = [9,pi/4];

[d1,d2,d3,d4] = findDist(0,pos,R)
[vel,rot] = phys(5,0,pos,m,M,R,1)   