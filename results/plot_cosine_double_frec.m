data = csvread('latest_result.txt');

chromosome = data(:,1);
first_step_time = 1;

first_step_lower_A = chromosome(2);
first_step_lower_W1 = chromosome(3);
first_step_lower_W2 = chromosome(4);
first_step_lower_fase = chromosome(5);
first_step_lower_ind_term = chromosome(6);

first_step_upper_A = chromosome(7);
first_step_upper_W1 = chromosome(8);
first_step_upper_W2 = chromosome(9);
first_step_upper_fase = chromosome(10);
first_step_upper_ind_term = chromosome(11);

first2_step_lower_A = chromosome(12);
first2_step_lower_W1 = chromosome(13);
first2_step_lower_W2 = chromosome(14);
first2_step_lower_fase = chromosome(15);
first2_step_lower_ind_term = chromosome(16);

first2_step_upper_A = chromosome(17);
first2_step_upper_W1 = chromosome(18);
first2_step_upper_W2 = chromosome(19);
first2_step_upper_fase = chromosome(20);
first2_step_upper_ind_term = chromosome(21);

x = [0:0.001:10];    

psi = x + first_step_upper_fase - floor((x + first_step_upper_fase)/((pi/first_step_upper_W1) + (pi/first_step_upper_W2))) * ((pi/first_step_upper_W1) + (pi/first_step_upper_W2));

if(first_step_upper_W1*psi < pi)
    first_step_upper = first_step_upper_A*cos(first_step_upper_W1*psi) + first_step_upper_ind_term;
else
    first_step_upper = first_step_upper_A*cos(first_step_upper_W2*(psi-(pi/first_step_upper_W1)+(pi/first_step_upper_W2))) + first_step_upper_ind_term;
end

psi = x + first_step_lower_fase - floor((x + first_step_lower_fase)/((pi/first_step_lower_W1) + (pi/first_step_lower_W2))) * ((pi/first_step_lower_W1) + (pi/first_step_lower_W2));

if(first_step_lower_W1*psi < pi)
    first_step_lower = first_step_lower_A*cos(first_step_lower_W1*psi) + first_step_lower_ind_term;
else
    first_step_lower = first_step_lower_A*cos(first_step_lower_W2*(psi-(pi/first_step_lower_W1)+(pi/first_step_lower_W2))) + first_step_lower_ind_term;
end


psi = x + first2_step_upper_fase - floor((x + first2_step_upper_fase)/((pi/first_step_upper_W1) + (pi/first2_step_upper_W2))) * ((pi/first2_step_upper_W1) + (pi/first2_step_upper_W2));

if(first_step_upper_W1*psi < pi)
    first_step_upper_r = first2_step_upper_A*cos(first2_step_upper_W1*psi) + first2_step_upper_ind_term;
else
    first_step_upper_r = first2_step_upper_A*cos(first2_step_upper_W2*(psi-(pi/first2_step_upper_W1)+(pi/first2_step_upper_W2))) + first2_step_upper_ind_term;
end

psi = x + first2_step_lower_fase - floor((x + first2_step_lower_fase)/((pi/first2_step_lower_W1) + (pi/first2_step_lower_W2))) * ((pi/first2_step_lower_W1) + (pi/first2_step_lower_W2));

if(first_step_lower_W1*psi < pi)
    first_step_lower_r = first2_step_lower_A*cos(first2_step_lower_W1*psi) + first2_step_lower_ind_term;
else
    first_step_lower_r = first2_step_lower_A*cos(first2_step_lower_W2*(psi-(pi/first2_step_lower_W1)+(pi/first2_step_lower_W2))) + first2_step_lower_ind_term;
end

subplot(2,2,1)
plot(x,first_step_upper,x,first_step_upper_r)
title('Actuador coseno doble frecuencia')
legend('Muslo izquierdo first','Muslo derecho first')

axis([0 first_step_time -50 50])

subplot(2,2,3)
plot(x,first_step_lower,x,first_step_lower_r)
title('Actuador coseno doble frecuencia')
legend('Pierna derecha first','Pierna derecha first')

axis([0 first_step_time -50 50])

lower_A = chromosome(22);
lower_W1 = chromosome(23);
lower_W2 = chromosome(24);
lower_fase = chromosome(25);
lower_ind_term = chromosome(26);

upper_A = chromosome(27);
upper_W1 = chromosome(28);
upper_W2 = chromosome(29);
upper_fase = chromosome(30);
upper_ind_term = chromosome(31);  

psi = x + upper_fase - floor((x + upper_fase)/((pi/upper_W1) + (pi/upper_W2))) * ((pi/upper_W1) + (pi/upper_W2));

if(upper_W1*psi < pi)
    upper = upper_A*cos(upper_W1*psi) + upper_ind_term;
else
    upper = upper_A*cos(upper_W2*(psi-(pi/upper_W1)+(pi/upper_W2))) + upper_ind_term;
end

psi = x + lower_fase - floor((x + lower_fase)/((pi/lower_W1) + (pi/lower_W2))) * ((pi/lower_W1) + (pi/lower_W2));

if(lower_W1*psi < pi)
    lower = lower_A*cos(lower_W1*psi) + lower_ind_term;
else
    lower = lower_A*cos(lower_W2*(psi-(pi/lower_W1)+(pi/lower_W2))) + lower_ind_term;
end


psi = x + upper_fase + pi - floor((x + upper_fase + pi)/((pi/upper_W1) + (pi/upper_W2))) * ((pi/upper_W1) + (pi/upper_W2));

if(upper_W1*psi < pi)
    upper_r = upper_A*cos(upper_W1*psi) + upper_ind_term;
else
    upper_r = upper_A*cos(upper_W2*(psi-(pi/upper_W1)+(pi/upper_W2))) + upper_ind_term;
end

psi = x + lower_fase + pi - floor((x + lower_fase + pi)/((pi/lower_W1) + (pi/lower_W2))) * ((pi/lower_W1) + (pi/lower_W2));

if(lower_W1*psi < pi)
    lower_r = lower_A*cos(lower_W1*psi) + lower_ind_term;
else
    lower_r = lower_A*cos(lower_W2*(psi-(pi/lower_W1)+(pi/lower_W2))) + lower_ind_term;
end

subplot(2,2,2)
plot(x,upper,x,upper_r)
title('Actuador coseno doble frecuencia')
legend('Muslo izquierdo','Muslo derecho')

axis([first_step_time 3 -50 50])

subplot(2,2,4)
plot(x,lower,x,lower_r)
title('Actuador coseno doble frecuencia')
legend('Pierna izquierda','Pierna derecha')

axis([first_step_time 3 -50 50])