% % FOR PLOTING THE OUTPUT OF THE DSP PROCESSOR

% the estimates computed by the DSP processor 
x = [125 132 135 136 133 131 123 121 121 117 100 397 397 397 237 203 404 405 163 261 111 288 205 329 329 361 400 190 181 182 186 190 196 203 209 217 224 235 243 253 264 270 273 272 270 264 256 247 238 226 209 193 134 393 152 241 138 186 232 230 404 397 397 404 404 404 404 151 146 143 143 147 147 147 150 153 155 156 155 152 148 144 140 134 129 125 120 114 110 106 100 96 94 94 94 94 92 ];
disp(length(x));

N = 1764;
fs = 44100;
num_frames = 97;
time_axis = zeros(num_frames, 1);
shift = 441;

for i = 1:num_frames
    start_index = (i - 1) * shift + 1;
    time_axis(i) = (start_index + N/2 - 1) / fs;
end

figure
plot(time_axis,x,'b.-');
xlabel('Čas (s)');
ylabel('F0 (Hz)');
yline(50, 'r--', '50 Hz (min)');
yline(400, 'r--', '400 Hz (max)');
ylim([0 500]);
hold on;
grid on;
