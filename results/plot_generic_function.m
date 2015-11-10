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

x = [1:0.001:30];             

upper = upper_A * sin(upper_sin_frec * x + upper_fase) + upper_B * cos(upper_cos_frec * x + upper_fase) + upper_ind_term;

lower = lower_A * sin(lower_sin_frec * x + lower_fase) + lower_B * cos(lower_cos_frec * x + lower_fase) + lower_ind_term;

upper_r = upper_A * sin(upper_sin_frec * x + upper_fase + pi) + upper_B * cos(upper_cos_frec * x + upper_fase + pi) + upper_ind_term;

lower_r = lower_A * sin(lower_sin_frec * x + lower_fase + pi) + lower_B * cos(lower_cos_frec * x + lower_fase + pi) + lower_ind_term;

subplot(2,1,1)
plot(x,upper,x,upper_r)
title('Plot generic function')
legend('upper leg','upper_r leg')

subplot(2,1,2)
plot(x,lower,x,lower_r)
title('Plot generic function')
legend('lower leg','lower_r leg')