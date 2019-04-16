s=tf('s');  
G1 = (79.904901084040395228/(s+29.345361034211265098))*1/s;
G2 = (274/(s+101))*1/s;

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
G1 = (79.904901084040395228/(s+29.345361034211265098))*1/s;

figure(1)
margin(G1); grid on

figure(2)
step(feedback(G1,1))


%%
G1_Kp = G1*15;

figure(3)
margin(G1_Kp); grid on

figure(4)
step(feedback(G1_Kp,1))

%%
%Design lead - pm skal hæves 46,8 deg
%30 deg = 0,523598776 rad!!

rad = 0.523598776;
w0 = 30;
Beta = (1-sin(rad))/(1+sin(rad));
T=1/(w0*sqrt(Beta));
kc = sqrt(Beta);
GLead = ((1/Beta)*(s+(1/T)))/(s+(1/(Beta*T)))*kc;

figure(12)
margin(GLead)
grid on

%% Test lead regulator
G1_Kp_GLead = G1_Kp*GLead;
figure(13)
margin(G1_Kp_GLead)
grid on

%% Lag regulator

T = 30/10; %74.3 rad/s

%Vi fjerner (s+(1/(alpha*T))) fra nævneren fordi at vi ønsker en
%forstærkning på uendelig!!! Grunden til dette virker og vi fjerner den
%stationære fejl er fordi at vi tilføjer et nyt S led til vores
%overførselsfunktion = type 1 istedet for type 0!
Lag = (s+(1/T))/s;

figure(4)
margin(Lag)
grid on

%% Apply regulator
G1_Kp_Lead_Lag = G1_Kp_GLead*Lag;

figure(5)
margin(G1_Kp_Lead_Lag)
grid on;

figure(6)
step(feedback(G1_Kp_Lead_Lag,1)*1/s)
hold on
step(1/s)
hold off
grid on
