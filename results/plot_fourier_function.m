data = csvread('latest_result.txt');

chromosome = data(:,1);

lower_A1 = chromosome(2);
lower_A2 = chromosome(3);
lower_A3 = chromosome(4);
lower_A4 = chromosome(5);
lower_A5 = chromosome(6);
lower_A6 = chromosome(7);
lower_A7 = chromosome(8);
lower_A8 = chromosome(9);
lower_A9 = chromosome(10);
lower_A10 = chromosome(11);
lower_A11 = chromosome(12);
lower_A12 = chromosome(13);
lower_A13 = chromosome(14);
lower_A14 = chromosome(15);
lower_A15 = chromosome(16);
lower_A16 = chromosome(17);
lower_A17 = chromosome(18);
lower_A18 = chromosome(19);
lower_W = chromosome(20);
lower_fase = chromosome(21);
lower_ind_term = chromosome(22);

upper_A1 = chromosome(23);
upper_A2 = chromosome(24);
upper_A3 = chromosome(25);
upper_A4 = chromosome(26);
upper_A5 = chromosome(27);
upper_A6 = chromosome(28);
upper_A7 = chromosome(29);
upper_A8 = chromosome(30);
upper_A9 = chromosome(31);
upper_A10 = chromosome(32);
upper_A11 = chromosome(33);
upper_A12 = chromosome(34);
upper_A13 = chromosome(35);
upper_A14 = chromosome(36);
upper_A15 = chromosome(37);
upper_A16 = chromosome(38);
upper_A17 = chromosome(39);
upper_A18 = chromosome(40);
upper_W = chromosome(41);
upper_fase = chromosome(42);
upper_ind_term = chromosome(43);

x = [1:0.001:3];


upper_sines = upper_A1 * sin(upper_W * x + upper_fase) + upper_A2 * sin(2 * upper_W * x + upper_fase)+ upper_A3 * sin(3 * upper_W * x + upper_fase)+ upper_A4 * sin(4 * upper_W * x + upper_fase)+ upper_A5 * sin(5 * upper_W * x + upper_fase)+ upper_A6 * sin(6 * upper_W * x + upper_fase)+ upper_A7 * sin(7 * upper_W * x + upper_fase)+ upper_A8 * sin(8 * upper_W * x + upper_fase)+ upper_A9 * sin(9 * upper_W * x + upper_fase);

upper_cosines = upper_A10 * cos(upper_W * x + upper_fase) + upper_A11 * cos(2 * upper_W * x + upper_fase)+ upper_A12 * cos(3 * upper_W * x + upper_fase)+ upper_A13 * cos(4 * upper_W * x + upper_fase)+ upper_A14 * cos(5 * upper_W * x + upper_fase)+ upper_A15 * cos(6 * upper_W * x + upper_fase)+ upper_A16 * cos(7 * upper_W * x + upper_fase)+ upper_A17 * cos(8 * upper_W * x + upper_fase)+ upper_A18 * cos(9 * upper_W * x + upper_fase) + upper_ind_term;

lower_sines = lower_A1 * sin(lower_W * x + lower_fase) + lower_A2 * sin(2 * lower_W * x + lower_fase)+ lower_A3 * sin(3 * lower_W * x + lower_fase)+ lower_A4 * sin(4 * lower_W * x + lower_fase)+ lower_A5 * sin(5 * lower_W * x + lower_fase)+ lower_A6 * sin(6 * lower_W * x + lower_fase)+ lower_A7 * sin(7 * lower_W * x + lower_fase)+ lower_A8 * sin(8 * lower_W * x + lower_fase)+ lower_A9 * sin(9 * lower_W * x + lower_fase);

lower_cosines = lower_A10 * cos(lower_W * x + lower_fase) + lower_A11 * cos(2 * lower_W * x + lower_fase)+ lower_A12 * cos(3 * lower_W * x + lower_fase) + lower_A13 * cos(4 * lower_W * x + lower_fase)+ lower_A14 * cos(5 * lower_W * x + lower_fase)+ lower_A15 * cos(6 * lower_W * x + lower_fase)+ lower_A16 * cos(7 * lower_W * x + lower_fase)+ lower_A17 * cos(8 * lower_W * x + lower_fase)+ lower_A18 * cos(9 * lower_W * x + lower_fase)+ lower_ind_term;             

upper_y = upper_sines + upper_cosines;

lower_y = lower_sines + lower_cosines;



upper_sines_r = upper_A1 * sin(upper_W * x + upper_fase + pi) + upper_A2 * sin(2 * upper_W * x + upper_fase + pi);

upper_cosines_r = upper_A3 * cos(upper_W * x + upper_fase + pi) + upper_A4 * cos(2 * upper_W * x + upper_fase + pi) + upper_ind_term;

lower_sines_r = lower_A1 * sin(lower_W * x + lower_fase + pi) + lower_A2 * sin(2 * lower_W * x + lower_fase + pi);

lower_cosines_r = lower_A3 * cos(lower_W * x + lower_fase + pi) + lower_A4 * cos(2 * lower_W * x + lower_fase + pi) + lower_ind_term;           

upper_y_r = upper_sines_r + upper_cosines_r;

lower_y_r = lower_sines_r + lower_cosines_r;

%subplot(2,1,1)
plot(x,upper_y,'b',x,upper_y_r,'r','LineWidth',2)
%title('Actuador de Fourier de orden ','fontweight','bold','fontName','Calibri','fontsize',14)
lgnds = legend('Muslo izquierdo','Muslo derecho');
ch = get(lgnds,'Children');
th = findobj(ch,'Type','text');
set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)

figure(2)
plot(x,lower_y,'b',x,lower_y_r,'r','LineWidth',2)
%title('Actuador de Fourier de orden ','fontweight','bold','fontName','Calibri','fontsize',14)
lgnds = legend('Pierna izquierda','Pierna derecha');
ch = get(lgnds,'Children');
th = findobj(ch,'Type','text');
set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)