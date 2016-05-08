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

lower_A2 = chromosome(14);
lower_B2 = chromosome(15);
lower_sin_frec2 = chromosome(16);
lower_cos_frec2 = chromosome(17);
lower_fase2 = chromosome(18);
lower_ind_term2 = chromosome(19);

upper_A2 = chromosome(20);
upper_B2 = chromosome(21);
upper_sin_frec2 = chromosome(22);
upper_cos_frec2 = chromosome(23);
upper_fase2 = chromosome(24);
upper_ind_term2 = chromosome(25);

lower_A3 = chromosome(26);
lower_B3 = chromosome(27);
lower_sin_frec3 = chromosome(28);
lower_cos_frec3 = chromosome(29);
lower_fase3 = chromosome(30);
lower_ind_term3 = chromosome(31);

upper_A3 = chromosome(32);
upper_B3 = chromosome(33);
upper_sin_frec3 = chromosome(34);
upper_cos_frec3 = chromosome(35);
upper_fase3 = chromosome(36);
upper_ind_term3 = chromosome(37);

x = [0:0.001:0.7];
x2 = [0.7:0.001:5];

upper = upper_A * sin(upper_sin_frec * x + upper_fase) + upper_B * cos(upper_cos_frec * x + upper_fase) + upper_ind_term;

lower = lower_A * sin(lower_sin_frec * x + lower_fase) + lower_B * cos(lower_cos_frec * x + lower_fase) + lower_ind_term;

upper_r = upper_A2 * sin(upper_sin_frec2 * x + upper_fase2) + upper_B2 * cos(upper_cos_frec2 * x + upper_fase2) + upper_ind_term2;

lower_r = lower_A2 * sin(lower_sin_frec2 * x + lower_fase2) + lower_B2 * cos(lower_cos_frec2 * x + lower_fase2) + lower_ind_term2;

upper2 = upper_A3 * sin(upper_sin_frec3 * x2 + upper_fase3) + upper_B3 * cos(upper_cos_frec3 * x2 + upper_fase3) + upper_ind_term3;

lower2 = lower_A3 * sin(lower_sin_frec3 * x2 + lower_fase3) + lower_B3 * cos(lower_cos_frec3 * x2 + lower_fase3) + lower_ind_term3;

upper_r2 = upper_A3 * sin(upper_sin_frec3 * x2 + upper_fase3 + pi) + upper_B3 * cos(upper_cos_frec3 * x2 + upper_fase3 + pi) + upper_ind_term3;

lower_r2 = lower_A3 * sin(lower_sin_frec3 * x2 + lower_fase3 + pi) + lower_B3 * cos(lower_cos_frec3 * x2 + lower_fase3 + pi) + lower_ind_term3;

%subplot(2,1,1)
%plot(x,upper,'b',x,upper_r,'r','LineWidth',2)
%title('Actuador gen�rico','fontweight','bold','fontName','Calibri','fontsize',14)
%lgnds = legend('Muslo izquierdo','Muslo derecho');
%ch = get(lgnds,'Children');
%th = findobj(ch,'Type','text');
%set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
%xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
%ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)

%figure(2)
plot([x,x2],[lower,lower2],'b','LineWidth',5,[x,x2],[lower_r,lower_r2],'r','LineWidth',5)
%title('Actuador gen�rico','fontweight','bold','fontName','Calibri','fontsize',14)
lgnds = legend('Pierna izquierda','Pierna derecha');
ch = get(lgnds,'Children');
th = findobj(ch,'Type','text');
set(th,'fontweight','bold','fontName','Calibri','fontsize',12);
xlabel('Tiempo (s)','fontweight','bold','fontName','Calibri','fontsize',12)
ylabel('f(t)','fontweight','bold','fontName','Calibri','fontsize',12)
