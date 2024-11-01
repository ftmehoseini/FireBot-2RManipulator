clc ; clear ; close all ; 
%% Geometry 
L1 = 0.17; 
L2 = 0.19; % L2 > 16.5 !!! 
% The relative coordinates of the manipulator's base relative to the main coordinates
% The main coordinates are on the middle of the bottom side of the box
scale = 8 ; % scale parameter 

%% direct kinematic 
teta1ub = 170 ; teta1lb = 55   ; % teta1 upper bound and lower bound 
teta2ub = 160 ; teta2lb = 60  ; % teta1 upper bound and lower bound 

[teta1,teta2] = meshgrid(teta1lb:10:teta1ub,teta2lb:1:teta2ub) ;
x = L1*cosd(teta1) + L2*cosd(teta1+teta2) ; 
y = L1*sind(teta1) + L2*sind(teta1+teta2) ; 

plot(x,y,'Color','blue','LineStyle','-') ; 
hold on ; 


x0 = -0.3 ; y0 = -0.1 ;  %The coordinates of the lower left corner
x1 = linspace(0+x0,23.5+x0 , 100) ; 
y1 = linspace(0+y0, 23.5+y0 , 100) ; 

[xx,yy] = meshgrid(0+x0:0.005:0.235+x0,0+y0:0.005:0.235+y0) ;
plot(xx,yy,'Color','red') ;
hold on ; 
[xd , yd] = meshgrid(linspace(x0+0.235/(scale*2),x0+0.235-0.235/(scale*2),scale-1) , linspace(y0+0.235/(scale*2),y0+0.235-0.235/(scale*2),scale-1) ) ; 
plot(xd,yd,'*','Color','black') ;

% teta2d = zeros(scale-1) ; teta1d = zeros(scale-1) ; 
teta2d = acos(((xd).^2 + (yd).^2 - (L1)^2 - (L2)^2) / (2 * L1 * L2)) ;
teta1d = atan(yd./xd) - atan((L2 * sin(teta2d))./(L1 + L2 *cos(teta2d)));

teta2d = teta2d*180/pi ; 
teta1d = teta1d*180/pi ; 





