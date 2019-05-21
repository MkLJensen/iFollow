s=tf('s');  
G1 = (82.049903762029746282/(s+30.13312094819631417))*1/s;
G2 = (292/(s+107))*1/s;

figure(1)
margin(G1); grid on

figure(2)
margin(G2); grid on

figure(3)
step(feedback(G1,1)*1/s)
hold on
step(feedback(G2,1)*1/s)
step(1/s)
hold off


%%
G1 = (82.049903762029746282/(s+30.13312094819631417))*1/s;

figure(1)
margin(G1); grid on

figure(2)
step(feedback(G1,1))


%%

% Vi antager at en person accelererer til konstant hastighed (ca. 5km/t) på
% 1 sekund, hvilket svarer til 1Hz båndbredde. Derfor designes Kp til en
% fasemargins frekvens der er 10 gange højere = 10 Hz. 

Kp = 50.1187;
G1_Kp = G1*Kp;

figure(3)
margin(G1_Kp); grid on

figure(4)
step(feedback(G1_Kp,1))

%%
%Design lead - pm skal hæves 50 deg;
%50 deg = 0,872664626 rad!!

rad = 0.872664626;
w0 = 66;
Beta = (1-sin(rad))/(1+sin(rad));
T=1/(w0*sqrt(Beta));
kc = sqrt(Beta);
GLead = ((1/Beta)*(s+(1/T)))/(s+(1/(Beta*T)))*kc;

figure(5)
margin(GLead)
grid on

%% Test lead regulator
G1_Kp_GLead = G1_Kp*GLead;
figure(6)
margin(G1_Kp_GLead)
grid on

%% fasemargins tab grundet Sample hold. 
Ts = 0.002;
Gsh = exp(-s*Ts/2);

margin(G1_Kp_GLead*Gsh)
grid on;

% Ud fra denne kan vi se at vi mister 4deg fasemargin, hvilket vi stadig er okay med, da vi ligger over 70 deg. Dette er fint for vores system.  
%% z-transformering

Gc_z = c2d((Kp*GLead),Ts,'tustin')

% Hermed får vi vores funktion til digital regulering. 
