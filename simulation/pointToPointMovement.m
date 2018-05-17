clear all
close all
clc

%% TO-DO
% add current velocity of each line to simulation?

%% Required Files
% MovePayload.m -> used to calculate old and new points for center payload

%% SIMULATION SETTINGS

gifCreate = 0;              % change this to 1 for gif creation
filename = 'my_gif.gif';    % set output gif filename here

%% Enviromental Constants and Simulation Options
% NOTE: all dimensions are given in INCHES or FRACTIONS OF AN INCH

% DIAMETER of the RING (rolling frame)
frame_size = 15;

% LENGTH of PAYLOAD SIDE 
% note! assumes payload is a SQUARE!
payload_size = 2.5;

% point to start from
start_point = [0,-5];

% point to end on
stop_point = [0,5];

% frames per time resolution
linear_resolution = 100;

%% moving from a start point to a stop point in discrete animated steps

% frame constants to be used in plotting
theta = linspace(0,2*pi);
frame_x = (frame_size / 2)*cos(theta);
frame_y = (frame_size / 2)*sin(theta);

% Setting motor locations
motor_locations = [[frame_size / 2, 0]; ...
                   [0, frame_size / 2]; ...
                   [-(frame_size / 2), 0]; ...
                   [0, -(frame_size / 2)]];

% Setting initl. payload location and points relative to that
payload_location = start_point;

% Set a figure handle
h = figure;

% these get drawn once
hold on
plot(frame_x, frame_y, 'k', 'LineWidth', 5);
axis equal
plot(motor_locations(:,1), motor_locations(:,2), 'r.', 'MarkerSize', 25);

payload_corners = MovePayload(payload_size, payload_location);

% REDRAW EVERY MOVEMENT
% payload center and corners
plot_center_point = plot(payload_location(:,1),payload_location(:,2),'rx');
plot_payload_corners = plot(payload_corners(:,1),payload_corners(:,2),'r.', 'MarkerSize', 3);
% payload border
plot_b1 = plot([payload_corners(1,1) payload_corners(2,1)], [payload_corners(1,2) payload_corners(2,2)], '--k');
plot_b2 = plot([payload_corners(2,1) payload_corners(3,1)], [payload_corners(2,2) payload_corners(3,2)], '--k');
plot_b3 = plot([payload_corners(3,1) payload_corners(4,1)], [payload_corners(3,2) payload_corners(4,2)], '--k');
plot_b4 = plot([payload_corners(4,1) payload_corners(1,1)], [payload_corners(4,2) payload_corners(1,2)], '--k');
% lines from motors to payload corners
plot_line1 = plot([payload_corners(1,1) motor_locations(1,1)], [payload_corners(1,2) motor_locations(1,2)], 'k', 'LineWidth', 1);
plot_line2 = plot([payload_corners(2,1) motor_locations(2,1)], [payload_corners(2,2) motor_locations(2,2)], 'k', 'LineWidth', 1);
plot_line3 = plot([payload_corners(3,1) motor_locations(3,1)], [payload_corners(3,2) motor_locations(3,2)], 'k', 'LineWidth', 1);
plot_line4 = plot([payload_corners(4,1) motor_locations(4,1)], [payload_corners(4,2) motor_locations(4,2)], 'k', 'LineWidth', 1);

%% Beginning of movement process

% get distance between two points
dist = pdist([start_point; stop_point], 'euclidean');

% x and y movement per time unit
x_dist_unit = abs(stop_point(1,1) - start_point(1,1)) / linear_resolution;
y_dist_unit = abs(stop_point(1,2) - start_point(1,2)) / linear_resolution;

center_points = []; %x and y coordinates for center of payload over linear time 
line_lengths  = []; %length of strings for each motor over linear time

for i = 1:1:linear_resolution    
    
   dist_m0 = pdist([payload_corners(1,:) ; motor_locations(1,:)], 'euclidean');
   dist_m1 = pdist([payload_corners(2,:) ; motor_locations(2,:)], 'euclidean');
   dist_m2 = pdist([payload_corners(3,:) ; motor_locations(3,:)], 'euclidean');
   dist_m3 = pdist([payload_corners(4,:) ; motor_locations(4,:)], 'euclidean');
   line_lengths = [line_lengths; dist_m0, dist_m1, dist_m2, dist_m3];
   center_points  = [center_points ; payload_location];
   
   if start_point(1,1) <= stop_point(1,1)
       payload_location(1,1) = payload_location(1,1) + x_dist_unit;
   else
       payload_location(1,1) = payload_location(1,1) - x_dist_unit;
   end
   
   if start_point(1,2) <= stop_point(1,2)
       payload_location(1,2) = payload_location(1,2) + y_dist_unit;
   else
       payload_location(1,2) = payload_location(1,2) - y_dist_unit;
   end
   
   % moving center point
   set(plot_center_point, 'XData', payload_location(1,1), 'YData', payload_location(1,2));
   
   % moving payload corners
   payload_corners = MovePayload(payload_size, payload_location);
   set(plot_payload_corners, 'XData', payload_corners(:,1), 'YData', payload_corners(:,2));
   
   % moving payload frame
   set(plot_b1, 'XData', [payload_corners(1,1) payload_corners(2,1)], 'YData',[payload_corners(1,2) payload_corners(2,2)]); 
   set(plot_b2, 'XData', [payload_corners(2,1) payload_corners(3,1)], 'YData',[payload_corners(2,2) payload_corners(3,2)]); 
   set(plot_b3, 'XData', [payload_corners(3,1) payload_corners(4,1)], 'YData',[payload_corners(3,2) payload_corners(4,2)]); 
   set(plot_b4, 'XData', [payload_corners(4,1) payload_corners(1,1)], 'YData',[payload_corners(4,2) payload_corners(1,2)]); 
   
   % moving strings attached to payload
   set(plot_line1, 'XData', [payload_corners(1,1) motor_locations(1,1)], 'YData', [payload_corners(1,2) motor_locations(1,2)]);
   set(plot_line2, 'XData', [payload_corners(2,1) motor_locations(2,1)], 'YData', [payload_corners(2,2) motor_locations(2,2)]);
   set(plot_line3, 'XData', [payload_corners(3,1) motor_locations(3,1)], 'YData', [payload_corners(3,2) motor_locations(3,2)]);
   set(plot_line4, 'XData', [payload_corners(4,1) motor_locations(4,1)], 'YData', [payload_corners(4,2) motor_locations(4,2)]);
      
   %pause(0.1)
   drawnow
   
   if gifCreate == 1
       frame = getframe(h); 
       im = frame2im(frame); 
       [imind,cm] = rgb2ind(im,256); 
       % Write to the GIF File 
       if i == 1 
          imwrite(imind,cm,filename,'gif', 'Loopcount',inf); 
       else 
          imwrite(imind,cm,filename,'gif','WriteMode','append'); 
       end  
   end
 
end