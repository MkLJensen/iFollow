%% Motor reguleringsteori
%% Motor fart regulator
%% Variabler
J   = 0.01;      % Motors intertia                       (kg.m^2)
D   = 0.1;       % Motors viscious friction              (N.m.s)
Kb  = 0.3663475; % Motors electromotive force constant   (V/rad/sec)
Kt  = 0.3663475; % Motors motor torque constant          (N.m/Amp)
R   = 1.27;      % Motors coil resistance                (Ohm)
L   = 0.0;       % Motors electric inductance            (H)
Ts  = 2.0593965; % Motors stall torque                   (N.m)
Is  = 9.4;       % Motors stall current                  (A)

%% Overf?ringsfunktion
s  = tf('s');
Gs = (Kt/(R/J))/(s*(s+(1/J)*(D+(Kt*Kb)/R)));    % Theta/Ea -- vel/V
Gacc = 1/(R/Kt*(J*s+D)+Kb);

%% Beregning af diverse features
Ea          = 12;       % Indgangssp?nding (V)
w_tomgang   = Ea/Kb;    % Tomgangs hastighed I = 0A (rad/s)

%% Regulering
Kp = 3;                         % Proporionalitetsfaktor
Gclosed = feedback(Gs*Kp,1);    % Closed-loop TF with Kp
step(feedback(Gs*Kp,1));        % Test af rise-time p? step