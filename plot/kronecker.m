for iter=15:20
    display('yes')
    g = kronecker_generator(iter, 2);
    [n, m] = size(g);
    filename = strcat('graph', int2str(iter), '.txt');
    fileID = fopen(filename, 'w');
    for i=1:m
        fprintf(fileID,'%d %d\n', g(1, i), g(2, i));
    end
    fclose(fileID);
    
end