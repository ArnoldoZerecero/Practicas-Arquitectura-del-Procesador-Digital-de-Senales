clear all
a = [1,2,3;4,5,6;7,8,9];
b = [1,2,3;4,5,6;7,8,9];
if size(a) == size(b) %Si los tamaños son iguales
    [sx,sy] = size(a); %Se toman los valores del número de renglones y el número de columnas
    if sx == sy %Si la matriz es cuadrada
        disp ('Las matrices son cuadradas.')
        
        Size = sx; %dimensión de ambas matrices
        d = zeros(Size,Size); %matriz resultante
        i = 1; %indice de renglón de d
        j = 1; %índice de columna de d
        ax = 1; %indice de renglón de a
        ab = 1; %índice de columna de a, e índice de renglón de b. En la multiplicación de matrices, los elementos a operar siempre comparten un índice de columna (a) con el índice del renglón del otro (b) en todos los casos,
        by = 1; %índice de columna de b
        
        for ax = 1:Size %el renglón de a es el último en incrementarse hasta igualar el tamaño de las matrices, por lo que cuando sea igual a Size, nos indica que el sistema se encuentra en el último ciclo de la multiplicación
            for by = 1:Size %este índice debe incrementarse y posteriormente cambiar intermitentemente cada Size veces
                ResultadoSuma = 0; %acumulador para el resultado de la suma de las multiplicaciones entre elementos
                for ab = 1:Size %este índice se incrementa o reinicia en cada una de las partes de la multiplicación
                    Elemento1 = a(ax,ab);
                    Elemento2 = b(ab,by);
                    ResultadoSuma = ResultadoSuma + Elemento1*Elemento2; %se almacena en c cada resultado de la multiplicación Elemento1*Elemento2
                end
                %Por último, se almacena el resultado de la suma en cierta posición de la matriz resultante
                d(i,j) = ResultadoSuma; %se almacena cada resultado en la posición dictada por los índices
                if j ~= Size %se ajustan los índices para ir llenando cada espacio
                    j = j + 1;
                else
                    j = 1;
                    i = i + 1;
                end
            end
        end
        disp('Resultado =')
        disp(d)
    else
        disp ('Error. Las matrices no son cuadradas.')
    end
else
    disp ('Error. Las matrices no son del mismo tamaño.')
end


    