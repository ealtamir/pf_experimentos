% Put this inside bin/Debug and execute it to plot the mean per generation

data = tdfread('bog4.dat');

generations = data.x0;
mean = data.x00x2E0643372;
deviation = data.x00x2E0499757;

hold on
plot(generations, mean)
% errorbar(generations, mean, -deviation/2, deviation/2)

