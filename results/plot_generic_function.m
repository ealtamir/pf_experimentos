data = csvread('latest_result.txt');

chromosome = data(:,1);

upper_A = chromosome(2);
upper_B = chromosome(3);
upper_sin_frec = chromosome(4);
upper_cos_frec = chromosome(5);
upper_fase = chromosome(6);
upper_ind_term = chromosome(7);

lower_A = chromosome(8);
lower_B = chromosome(9);
lower_sin_frec = chromosome(10);
lower_cos_frec = chromosome(11);
lower_fase = chromosome(12);
lower_ind_term = chromosome(13);

x = [1:0.001:10];             

upper = upper_A * sin(upper_sin_frec * x + upper_fase) + upper_B * cos(upper_cos_frec * x + upper_fase) + upper_ind_term;

lower = lower_A * sin(lower_sin_frec * x + lower_fase) + lower_B * cos(lower_cos_frec * x + lower_fase) + lower_ind_term;

plot(x,upper,x,lower)
title('Plot generic function')
legend('upper leg','lower leg')