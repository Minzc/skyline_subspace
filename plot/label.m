test = load('test.mat');

c = zeros(1,500);
d = containers.Map;
for i=1:10
    t = strsplit(char(test.C(i)), '/');
    t = char(t(1));
    d(t) = i;
end
test.label = zeros(1,500);
for i=1:500
    a = test.Itest(i);
    b = strsplit(char(a), '/');
    test.label(i) = d(char(b(3)));
end

save('label.mat', 'test');