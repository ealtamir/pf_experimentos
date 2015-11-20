data = csvread('latest_result.txt');

chromosome = data(:,1);

lower_A = chromosome(2);
lower_W1 = chromosome(3);
lower_W2 = chromosome(4);
lower_fase = chromosome(5);
lower_ind_term = chromosome(6);

upper_A = chromosome(7);
upper_W1 = chromosome(8);
upper_W2 = chromosome(9);
upper_fase = chromosome(10);
upper_ind_term = chromosome(11);

x = [1:0.001:10];    

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

subplot(2,1,1)
plot(x,upper,x,upper_r)
title('Plot generic function')
legend('upper leg','upper right leg')

subplot(2,1,2)
plot(x,lower,x,lower_r)
title('Plot generic function')
legend('lower leg','lower right leg')