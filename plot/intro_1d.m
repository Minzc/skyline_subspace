h1=figure(1);clf
subplot(4,1,1);
hold on
xlim([0,5]);ylim([-1,1])

%arrow
[arrowX,arrowY]=dsxy2figxy([0,5],[0,0]);
annotation('arrow', arrowX, arrowY)

%crosses
x=[1,2,3,4];
plot(x, 0, 'ko','markersize', 10)

text([1,2,3,4], [1,-1,1,-1]/2, {'{a,d}(1)', 'b(2)', 'c(3)', 'e(4)'}, 'interpreter', 'latex', 'FontSize', 20)
axis off

saveas(gcf, 'intro_x', 'eps');

h2=figure(2);clf
subplot(4,1,1);
hold on
xlim([0,5]);ylim([-1,1])

%arrow
[arrowX,arrowY]=dsxy2figxy([0,5],[0,0]);
annotation('arrow', arrowX, arrowY)

%crosses
x=[1,2,3,4];
plot(x, 0, 'ko','markersize', 10)

text([1,2,3,4], [1,-1,1,-1]/2, {'c(1)', 'b(2)', '{a,e}(3)', 'd(4)'}, 'interpreter', 'latex', 'FontSize', 20)
axis off

saveas(gcf, 'intro_y', 'eps');


