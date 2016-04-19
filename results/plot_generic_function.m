data = csvread('latest_result.txt');

chromosome = data(:,1);

lower_A = chromosome(2);
lower_B = chromosome(3);
lower_sin_frec = chromosome(4);
lower_cos_frec = chromosome(5);
lower_fase = chromosome(6);
lower_ind_term = chromosome(7);

upper_A = chromosome(8);
upper_B = chromosome(9);
upper_sin_frec = chromosome(10);
upper_cos_frec = chromosome(11);
upper_fase = chromosome(12);
upper_ind_term = chromosome(13);

x = [1:0.001:3];             

upper = upper_A * sin(upper_sin_frec * x + upper_fase) + upper_B * cos(upper_cos_frec * x + upper_fase) + upper_ind_term;

lower = lower_A * sin(lower_sin_frec * x + lower_fase) + lower_B * cos(lower_cos_frec * x + lower_fase) + lower_ind_term;

upper_r = upper_A * sin(upper_sin_frec * x + upper_fase + pi) + upper_B * cos(upper_cos_frec * x + upper_fase + pi) + upper_ind_term;

lower_r = lower_A * sin(lower_sin_frec * x + lower_fase + pi) + lower_B * cos(lower_cos_frec * x + lower_fase + pi) + lower_ind_term;

%subplot(2,1,1)
plot(x,upper,'b',x,upper_r,'r','LineWidth',2)
%title('Actuador genérico','fontweight','bold','fontName','Calibri','fontsize',14)
lgnds = legend('Muslo izquierdo','Muslo derecho');
ch = get(lgnds,'Children');
th = findobj(ch,'Type','text');
set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)

figure(2)
plot(x,lower,'b',x,lower_r,'r','LineWidth',2)
%title('Actuador genérico','fontweight','bold','fontName','Calibri','fontsize',14)
lgnds = legend('Pierna izquierda','Pierna derecha');
ch = get(lgnds,'Children');
th = findobj(ch,'Type','text');
set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)