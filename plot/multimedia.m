im = imread('frame1.bmp');
im = rgb2gray(im);
im = imresize(im, [64, 64]);
im = im2double(im); % now in 0 .. 1.0
im = fix(im*15); % truncate to int 0..15
im = im/15; % back to float -- in 0 .. 1.0
Fs=8000; % sampling frequency
freq = zeros(64,1); % 64-vector
freq(32) = 440.0; % center frequencies around "A":

for m = 33 : 64
    freq(m) = freq(m-1) * 2^(1.0/12.0);
end
for m = 31:-1:1
    freq(m) = freq(m+1) * 2^(-1.0/12.0);
end
