t  = 1:0.001:10;                                                 % Time Vector
load center10_20_40Hz_11s.log
s = center10_20_40Hz_11s./6842 ;                                                 % Signal Vector
Ts = mean(diff(t));                                         % Sampling Time
Fs = 1/Ts;                                                  % Sampling Frequency
Fn = Fs/2;                                                  % Nyquist Frequency
L  = length(s);
fts = fft(s)/L;                                             % Normalised Fourier Transform
Fv = linspace(0, 1, fix(L/2)+1)*Fn;                         % Frequency Vector
Iv = 1:length(Fv);                                          % Index Vector
amp_fts = abs(fts(Iv))*2;                                   % Spectrum Amplitude
phs_fts = angle(fts(Iv));                                   % Spectrum Phase
subplot(2,1,1)
plot(Fv,phs_fts/pi*180)
subplot(2,1,2)
plot(Fv,amp_fts)