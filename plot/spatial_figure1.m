xy = [[1, 2, 2, 0, 3, 4]; [1, 2, 3, 0, 2, 2]];

x_width=4;
y_width=4;
set(gcf, 'PaperPosition', [1 1 x_width y_width]);

%figure(1);
set(gca,'box','off')
plot(xy(1,:), xy(2,:), 'o');
axis equal
axis([-1 5 -1 4])
radii = [sqrt(2), 1, 1, 2];
centers = [[1, 1]; [3, 2]; [4, 2]; [4, 2]];

offset = -0.2;

%viscircles(centers, radii);
text(1 + offset, 1 + offset, 'u:(1, 1)');
text(2 + offset, 2 + offset, 'q:(2, 2)');
text(0 + offset, 0 + offset, 'v:(0, 0)');
text(2 + offset, 3 + offset, 'x:(2, 3)');
text(3 + offset, 2 + offset, 'y:(3, 2)');
text(4 + offset, 2 + offset, 'w:(4, 2)');

saveas(gcf, 'spatial_figure', 'eps');