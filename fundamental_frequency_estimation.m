% use autocorrelation method to estimate fundamental frequency of the
% signal. Plot the estimates as the function of time

file_path = 'tested_recording.wav';
[speech_signal, fs] = audioread(file_path);

disp(fs);

% Parameters
N = round(0.04/(1/fs));  % Lenght of the segment = 40 ms
shift = round(N/4);      % Shift of the next segment from the current segment (75% overlap)
num_frames = floor((length(speech_signal) - N) / shift) + 1; % number of frames
disp(num_frames);

% number of samples corresponding to the range of frequencies where the 
% estimates are expected (that is 50 to 400 Hz)
k_min = round(fs/400);
k_max = round(fs/50);

F0_estimates = zeros(num_frames, 1);
time_axis = zeros(num_frames, 1);

% Hamming window
w = hamming(N);

for i = 1:num_frames
    % Compute start and end index of the current segment 
    % in the input signal
    start_index = (i - 1) * shift + 1;
    end_index = start_index + N - 1;

    % extract the segment from the input signal
    segment = speech_signal(start_index:end_index);

    % Remove DC bias
    mu = mean(segment);
    segment_centered = segment - mu;

    % Apply hamming window
    segment_windowed = segment_centered .* w;


    % autocorrelation
    R = xcorr(segment_windowed, 'none'); 
    R_positive = R(N : end);

    % take only the relevant range of the autocorrelation function (k_min to k_max)
    R_relevant = R_positive(k_min + 1 : k_max + 1);

    % find maximum of autocorr. function
    [max_corr_val, k_peak_idx] = max(R_relevant);
    k_peak = k_peak_idx + k_min - 1;

    % quadratic interpolation
    if k_peak > k_min && k_peak < k_max
        R_minus = R_positive(k_peak);   
        R_center = R_positive(k_peak + 1);
        R_plus = R_positive(k_peak + 2);

        % k_interp = k_peak + 0.5 * (a - c) / (a - 2b + c)
        k_interp = k_peak + 0.5 * (R_minus - R_plus) / (R_minus - 2*R_center + R_plus);

        T0_samples = k_interp;
    else
        T0_samples = k_peak;
    end

    
    F0_estimates(i) =  fs / T0_samples;
    time_axis(i) = (start_index + N/2 - 1) / fs;

end

% PLOT
figure;
plot((1:length(speech_signal))/fs, speech_signal);
xlabel('Čas (s)');
ylabel('Amplituda');

figure
plot(time_axis, F0_estimates, 'b.-');
hold on;
yline(50, 'r--', '50 Hz (min)');
yline(400, 'r--', '400 Hz (max)');
xlabel('Čas (s)');
ylabel('F0 (Hz)');
ylim([0 500]);
grid on;

