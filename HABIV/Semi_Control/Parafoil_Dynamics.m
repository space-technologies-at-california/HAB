

%Constants
g = 32.174; %Acceleration due to gravity
W = 100; %Payload weight
A = 3; %Payload characteristic area
CP = 2; %Payload Drag Coefficient
CS = 0.5; %Payload Side Force Coefficient
S = 20; %Aerodynamic area of canopy
WS = 10; %Canopy wing 38
CDi = 0.01; %Initial canopy Drag Coefficient
CLi = 0.0; %Initial canop Lift Coefficient
CD = 0.2; %Inflated canopy Drag Coefficient
CL = 1.0; %Inflated canopy Lift Coefficient
CR= CL + CD; %Resultant Coefficient
e = 1.0; %Oswald Efficiency Factor
delTi = 5; %Inflation time

%Convert from Geodetic to Cartesian Coodinates
[lat,lon,h] = geodetic2enu(68.6719,44.8831,15000,68.6719,44.8831,0,wgs84Ellipsoid)/
;
function[rho,T,P]=density(h)
if h<= 16000 % troposphere
    T = 59 - 0.00356.*h; %deg F Temperature
    P = 2116.*((T+459.7)./518.6).5.256; %lbs/ft2 pressure
end
rho = P/(1718.*(T+459.7)); %slugs/ft3 density

end

%External Force Equations
V = ((2W)/(rhoS))2*(1/(CR2).25); %Velocity
L = (1/2)*rho*(V^2)*2*S*C*L); %Inflated Lift force
D = (1/2rhoV2SCD); %Inflated Drag force
D = (1/2rhoV2ACP); %Payload Drag force
R = (L2+D2).5; %Inflated Resultant force
gamma = atand(CD/CL); %Flight Path Angle
Vh = V*cos(gamma); %Horizontal veloctiy
Vv = V*sin(gamma); %Vertical velocity

%Force  Equations
Fh = Lsin(gamma)-Dcos(gamma); %Horizontal force
Fv = Lcos(gamma)+Dsin(gamma)-W; %Vertical force

