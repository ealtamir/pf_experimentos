data = csvread('latest_result.txt');

chromosome = data(:,1);

upper_A1 = chromosome(2);
upper_A2 = chromosome(3);
upper_A3 = chromosome(4);
upper_A4 = chromosome(5);
upper_W = chromosome(6);
upper_fase = chromosome(7);
upper_ind_term = chromosome(8);

lower_A1 = chromosome(9);
lower_A2 = chromosome(10);
lower_A3 = chromosome(11);
lower_A4 = chromosome(12);
lower_W = chromosome(13);
lower_fase = chromosome(14);
lower_ind_term = chromosome(15);


upper_sines = upper_A1 * sin(upper_W * x + upper_fase) + upper_A2 * sin(2 * upper_W * x + upper_fase);

upper_cosines = upper_A3 * cos(upper_W * x + upper_fase) + upper_A4 * cos(2 * upper_W * x + upper_fase) + upper_ind_term;

lower_sines = lower_A1 * sin(lower_W * x + lower_fase) + lower_A2 * sin(2 * lower_W * x + lower_fase);

lower_cosines = lower_A3 * cos(lower_W * x + lower_fase) + lower_A4 * cos(2 * lower_W * x + lower_fase) + lower_ind_term;


x = [1:0.001:10];             

upper_y = upper_sines + upper_cosines;

lower_y = lower_sines + lower_cosines;

plot(x,upper_y,x,lower_y)