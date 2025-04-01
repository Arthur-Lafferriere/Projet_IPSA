clear all
close all
%% Question
%% 1)
N=2000; %Number of samples

bits=randi([0,1],1,N);

symbole=2*bits-1;

figure;
stem((1:N), symbole);
xlabel('Number of samples');
title('Emitted symbols');

%% 2)
beta_values=[0.25,0.5,2,4];

figure;
for i = 1:length(beta_values)
    k = 1:3;
    w = 0.5*(1+cos(2*pi*(k-1)/beta_values(i)));
    
    subplot(2, 2, i);
    stem(k, w);
    title(['Canal pour \beta = ', num2str(beta_values(i))]);
    xlabel('k');
    ylabel('w(k)');
    ylim([0 1.1]);
    grid on;
end

%% 3)
beta=0.25;
k=1:3;
variance=0.001;

w=0.5*(1+cos(2*pi*(k-1)/beta)); %Impulse response of the propagation channel filter

x=filter(w,1,symbole); %Filtered signal

noise=sqrt(variance)*randn(1, N); %Propagation channel noise

x=x+noise; %Noisy and filtered signal

figure;
plot((1:N), x,'-r');
xlabel('Number of samples');
title('Transmitted signal');
%% Channel equalization with Wiener filter
%% 6)
L=5; %filter order

function w_val = w_(k, beta)
    if k >= 1 && k <= 3
        w_val = 0.5 * (1 + cos(2*pi*(k-1)/beta));
    else
        w_val = 0;
    end
end

%---Computation of Rxx
Rxx =zeros(L);
for k=1:L
    for l=1:L
        Rxx(k, l)=0;
        for i=1:L-1
            Rxx(k, l)=Rxx(k, l)+w_(i,beta)*w_(i+l-k,beta);
        end
    end
end

r_dx=zeros(L,1);
for i=1:L
    r_dx(i)=w_(4-i,beta);
end

h_opt = inv(Rxx)*r_dx;
%% 7)
%--Filtered signal
y_eq = filter(h_opt,1,x);

%--Plot
figure;
plot((1:N), y_eq);
hold on
plot((1:N),x);
legend('Equalized signal','Emitted signal');

%% 8)
SNR = linspace(-50,10,80); %Several values of SNR (in dB)
SER= zeros(1,length(SNR));
w1=0.5*(1+cos(2*pi*(k-1)/beta));

for i=1:length(SNR)
    L=5;
    s=2*randi([0,1],1,N)-1;
    P_s=var(filter(w1,1,s));
    sigma_u=sqrt(P_s./db2pow(SNR));
    noise1=sigma_u(i)*randn(1, N);
    y=filter(w1,1,s)+noise1;

    %-- Wiener filtering
    y_eq = filter(h_opt,1,y);

    s_est=zeros(1,N);
    s_est(y_eq>=0)=1;
    s_est(y_eq<0)=-1;
    
    SER(i) = sum(s_est~=[0 0 s(1:N-2)])/N;

end

figure;
plot(sigma_u,SER, '-o', 'LineWidth', 2);
xlabel('sigma_u^2');
ylabel('SER');
title('SER en fonction du sigma_u');
grid on;

figure;
plot(SNR,SER, '-o', 'LineWidth', 2);
xlabel('SNR (dB)');
ylabel('SER');
title('SER en fonction du SNR');
grid on;
%% 9&10) Channel equalization with LMs algorithm
N=2000;
L=5;

bits=randi([0,1],1,N);

symbole=2*bits-1;


beta=0.25;
k=1:3;
variance=0.001;

w=0.5*(1+cos(2*pi*(k-1)/beta)); %Impulse response of the propagation channel filter
x=filter(w,1,symbole); %Filtered signal
noise=sqrt(variance)*randn(1, N); %Propagation channel noise
x=x+noise; %Noisy and filtered signal


mu=0.01;
Number_iteration=2000;

% Initialisation des variables
h = 5*randn(L, 1);             % Initialisation des coefficients du filtre
error_norm = zeros(Number_iteration, 1);
error_history = zeros(Number_iteration, 1);
SER= zeros(Number_iteration, 1);
% Signal désiré (décalé)
d = [zeros(1, 2), symbole(1:N-2)];

% Algorithme LMS
for n = L:Number_iteration
    % Vecteur d'entrée
    x_n = x(n:-1:n-L+1)';
    
    % Prédiction
    y = h' * x_n;
    
    % Calcul de l'erreur
    error = d(n) - y;

    y_eq = filter(h,1,x);
    s_est=zeros(1,N);
    s_est(y_eq>=0)=1;
    s_est(y_eq<0)=-1;
    
    SER(n) = sum(s_est~=[0 0 symbole(1:N-2)])/N;
    
    % Mise à jour des coefficients selon la formule fournie
    h = h + mu * error * x_n;
    
    % Stockage de l'erreur
    error_history(n)=error;
    error_norm(n) = norm(h_opt-h)^2;
end

axe=(L:Number_iteration)';

figure;

subplot(2,2,1);
plot(symbole, 'LineWidth', 1.5);
title('signal emis d(n)');
xlabel("Nombre d'echantillon (n)");

subplot(2,2,2);
plot(filter(h_opt,1,x), 'LineWidth', 1.5);
title('signal recu égalisé y(n)');
xlabel("Nombre d'echantillon (n)");

subplot(2,2,4);
plot(axe,error_history(L:end), 'LineWidth', 1.5);
title('d(n)-h(n)^Ty(n)');
xlabel('Itérations');

subplot(2,2,3);
plot(axe,error_norm(L:end), 'LineWidth', 1.5);
title('||h_n - h_{opt}||²');
xlabel('Itérations');

%% 11 mu)

N = 2000;
L = 5;
bits = randi([0,1], 1, N);
symbole = 2*bits - 1;
beta = 0.25;
k = 1:3;
variance = 0.001;
w = 0.5*(1+cos(2*pi*(k-1)/beta)); % Impulse response of the propagation channel filter

% Définir différentes valeurs de mu
mu_values = [0.0001, 0.001, 0.01, 0.1];

% Initialiser les figures
figure;

% Boucle pour différentes valeurs de mu
for mu_idx = 1:length(mu_values)
    mu = mu_values(mu_idx);
    
    % Réinitialiser le signal pour chaque itération
    x = filter(w, 1, symbole);
    noise = sqrt(variance)*randn(1, N);
    x = x + noise;
    
    Number_iteration = 2000;
    
    % Initialisation des variables
    h = 5*randn(L, 1);
    error_norm = zeros(Number_iteration, 1);
    error_history = zeros(Number_iteration, 1);
    SER = zeros(Number_iteration, 1);
    
    % Signal désiré (décalé)
    d = [zeros(1, 2), symbole(1:N-2)];
    
    % Algorithme LMS
    for n = L:Number_iteration
        % Vecteur d'entrée
        x_n = x(n:-1:n-L+1)';
        
        % Prédiction
        y = h' * x_n;
        
        % Calcul de l'erreur
        error = d(n) - y;
        y_eq = filter(h, 1, x);
        
        s_est = zeros(1, N);
        s_est(y_eq >= 0) = 1;
        s_est(y_eq < 0) = -1;
        
        SER(n) = sum(s_est ~= [0 0 symbole(1:N-2)]) / N;
        
        % Mise à jour des coefficients
        h = h + mu * error * x_n;
        
        % Stockage de l'erreur
        error_history(n) = error;
        error_norm(n) = norm(h)^2;
    end
    
    % Tracer SER
    subplot(length(mu_values), 2, 1+2*(mu_idx-1));
    axe = (L:Number_iteration)';
    plot(axe, SER(L:end), 'LineWidth', 1.5, 'DisplayName', sprintf('µ = %.4f', mu));
    hold on;
    title('SER');
    xlabel('Itérations n');
    
    grid on;
    legend('show');
    
    % Tracer norme de l'erreur
    subplot(length(mu_values), 2, 2+2*(mu_idx-1));
    plot(axe, error_norm(L:end), 'LineWidth', 1.5, 'DisplayName', sprintf('µ = %.4f', mu));
    hold on;
    title('||hn - h{opt}||²');
    xlabel('Itérations n');
    grid on;
    legend('show');
end

% Ajuster la taille et la position de la figure
set(gcf, 'Position', [100, 100, 1000, 800]);

%% 11 sigma)

N = 2000;
L = 5;
bits = randi([0,1], 1, N);
symbole = 2*bits - 1;
beta = 0.25;
k = 1:3;
variance = 0.001;
w = 0.5*(1+cos(2*pi*(k-1)/beta)); % Impulse response of the propagation channel filter

% Définir différentes valeurs de mu
sigma = [0.01, 0.1, 1, 10];

% Initialiser les figures
figure;

% Boucle pour différentes valeurs de mu
for s_idx = 1:length(sigma)
    mu = 0.01;
    
    % Réinitialiser le signal pour chaque itération
    x = filter(w, 1, symbole);
    noise = sqrt(sigma(s_idx))*randn(1, N);
    x = x + noise;
    
    Number_iteration = 2000;
    
    % Initialisation des variables
    h = 5*randn(L, 1);
    error_norm = zeros(Number_iteration, 1);
    error_history = zeros(Number_iteration, 1);
    SER = zeros(Number_iteration, 1);
    
    % Signal désiré (décalé)
    d = [zeros(1, 2), symbole(1:N-2)];
    
    % Algorithme LMS
    for n = L:Number_iteration
        % Vecteur d'entrée
        x_n = x(n:-1:n-L+1)';
        
        % Prédiction
        y = h' * x_n;
        
        % Calcul de l'erreur
        error = d(n) - y;
        y_eq = filter(h, 1, x);
        
        s_est = zeros(1, N);
        s_est(y_eq >= 0) = 1;
        s_est(y_eq < 0) = -1;
        
        SER(n) = sum(s_est ~= [0 0 symbole(1:N-2)]) / N;
        
        % Mise à jour des coefficients
        h = h + mu * error * x_n;
        
        % Stockage de l'erreur
        error_history(n) = error;
        error_norm(n) = norm(h)^2;
    end
    
    % Tracer SER
    subplot(length(mu_values), 2, 1+2*(s_idx-1));
    axe = (L:Number_iteration)';
    plot(axe, SER(L:end), 'LineWidth', 1.5, 'DisplayName', sprintf('σ^2 = %.2f', sigma(s_idx)));
    hold on;
    title('SER');
    xlabel('Itérations n');
    
    grid on;
    legend('show');
    
    % Tracer norme de l'erreur
    subplot(length(mu_values), 2, 2+2*(s_idx-1));
    plot(axe, error_norm(L:end), 'LineWidth', 1.5, 'DisplayName', sprintf('σ^2 = %.2f', sigma(s_idx)));
    hold on;
    title('||hn - h{opt}||²');
    xlabel('Itérations n');
    grid on;
    legend('show');
end

% Ajuster la taille et la position de la figure
set(gcf, 'Position', [100, 100, 1000, 800]);