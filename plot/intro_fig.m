xy = [[1, 2, 3, 1, 4]; [3, 2, 1, 4, 3]];

x_width=4;
y_width=4;
set(gcf, 'PaperPosition', [1 1 x_width y_width]);

%figure(1);
plot(xy(1,:), xy(2,:), 'o');
axis equal
axis([0 5 0 5])
offset = -0.2;

%viscircles(centers, radii);
text(1 + offset, 3 + offset, 'a(1, 3)');
text(2 + offset, 2 + offset, 'b(2, 2)');
text(3 + offset, 1 + offset, 'c(3, 1)');
text(1 + offset, 4 + offset, 'd(1, 4)');
text(4 + offset, 3 + offset, 'e(4, 3)');



saveas(gcf, 'intro_xy', 'eps');

