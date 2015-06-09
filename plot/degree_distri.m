x_width=2.4;
y_width=1.8;
set(gcf, 'PaperPosition', [1 1 x_width*1.5 y_width*1.5]);
x = textread('fb_d.txt', '%d', 'whitespace', '');
hist(x, 30);
xlabel('number of degree');
saveas(gcf, 'fb_distri', 'eps');
clf;

set(gcf, 'PaperPosition', [1 1 x_width*1.5 y_width*1.5]);
x = textread('degree_distribution.txt', '%d', 'whitespace', '');
hist(x);
xlabel('number of degree');
saveas(gcf, 'DBLP_distri', 'eps');