% Put this inside bin/Debug and execute it to plot the mean per generation

data = csvread('output.dat');

generations = 1000;
populationSize = 20;
fitneses = data(:,2);
boxplotMatrix = zeros(populationSize, generations);

for i = 1:generations
    for j = 1:populationSize
        boxplotMatrix(j,i) = fitneses((i-1)*populationSize+j);
    end
end

% boxplot(boxplotMatrix)
plot(1:generations, mean(boxplotMatrix))