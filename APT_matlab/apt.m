function [predicted_score] = apt(error_map)
%eval: 计算单张失真图像的质量
%   输入图像是由C++代码段实现的error_map (float)，输出是预测的质量分数

% 输入的Error map首先使用Gaussian滤波器剔除孤立点

[row, col] = size(error_map);

gausFilter = fspecial('gaussian', [3, 3], 0.5);
gaus_map = imfilter(error_map, gausFilter, 'replicate');

% 计算Saliency map
saliency_map(:, :, 1) = gaus_map;
saliency_map(:, :, 2) = gaus_map;
saliency_map(:, :, 3) = gaus_map;

saliency_map = FES(saliency_map);
saliency_map = imresize(saliency_map, [row, col], 'nearest'); % FES原始提供的saliency map不够大
figure, imshow(saliency_map);
title('显著性图');

gamma = 100;
level = gamma / 255;

d_map = im2bw(saliency_map, level);

figure, imshow(d_map);
title('二值图');

predicted_score = 0;
end

