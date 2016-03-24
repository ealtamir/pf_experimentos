data = csvread('latest_result.txt');

chromosome = data(:,1);

lower_A1 = chromosome(2);
lower_A2 = chromosome(3);
lower_A3 = chromosome(4);
lower_A4 = chromosome(5);
lower_W = chromosome(6);
lower_fase = chromosome(7);
lower_ind_term = chromosome(8);

upper_A1 = chromosome(9);
upper_A2 = chromosome(10);
upper_A3 = chromosome(11);
upper_A4 = chromosome(12);
upper_W = chromosome(13);
upper_fase = chromosome(14);
upper_ind_term = chromosome(15);

x = [1:0.001:10];


upper_sines = upper_A1 * sin(upper_W * x + upper_fase) + upper_A2 * sin(2 * upper_W * x + upper_fase);

upper_cosines = upper_A3 * cos(upper_W * x + upper_fase) + upper_A4 * cos(2 * upper_W * x + upper_fase) + upper_ind_term;

lower_sines = lower_A1 * sin(lower_W * x + lower_fase) + lower_A2 * sin(2 * lower_W * x + lower_fase);

lower_cosines = lower_A3 * cos(lower_W * x + lower_fase) + lower_A4 * cos(2 * lower_W * x + lower_fase) + lower_ind_term;             

upper_y = upper_sines + upper_cosines;

lower_y = lower_sines + lower_cosines;



upper_sines_r = upper_A1 * sin(upper_W * x + upper_fase + pi) + upper_A2 * sin(2 * upper_W * x + upper_fase + pi);

upper_cosines_r = upper_A3 * cos(upper_W * x + upper_fase + pi) + upper_A4 * cos(2 * upper_W * x + upper_fase + pi) + upper_ind_term;

lower_sines_r = lower_A1 * sin(lower_W * x + lower_fase + pi) + lower_A2 * sin(2 * lower_W * x + lower_fase + pi);

lower_cosines_r = lower_A3 * cos(lower_W * x + lower_fase + pi) + lower_A4 * cos(2 * lower_W * x + lower_fase + pi) + lower_ind_term;           

upper_y_r = upper_sines_r + upper_cosines_r;

lower_y_r = lower_sines_r + lower_cosines_r;

subplot(2,1,1)
plot(x,upper_y,x,upper_y_r)
title('Actuador Fourier de orden')
legend('Pierna','Pierna derecha')
xlabel('t (s)')
ylabel('f(t)')

subplot(2,1,2)
plot(x,lower_y,x,lower_y_r)
title('Actuador Fourier de orden')
legend('Muslo','Muslo derecho')
xlabel('t (s)')
ylabel('f(t)')