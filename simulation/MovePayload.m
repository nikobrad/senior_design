function [ new_payload_points ] = MovePayload( payload_size, payload_location )
%MOVEPAYLOAD Applies shift of payload center to surrounding points
%   returns four corner points for moved payload after applying translation

% corners move counter-clockwise from (x, y = 0) to (x = 0, -y).
new_payload_points = [[payload_location(1,1) + ((payload_size * (2^.5))/2), payload_location(1,2)]; ...
                      [payload_location(1,1), payload_location(1,2) + ((payload_size * (2^.5))/2)]; ...
                      [payload_location(1,1) - ((payload_size * (2^.5))/2), payload_location(1,2)]; ... 
                      [payload_location(1,1), payload_location(1,2) - ((payload_size * (2^.5))/2)]];
                  
end

