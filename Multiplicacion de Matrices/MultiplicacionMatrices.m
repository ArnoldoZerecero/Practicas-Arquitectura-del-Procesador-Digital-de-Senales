clear all
a = [1,2,3;4,5,6;7,8,9];
b = [1,2,3;4,5,6;7,8,9];
if size(a) == size(b) %Si los tama�os son iguales
    [sx,sy] = size(a); %Se toman los valores del n�mero de renglones y el n�mero de columnas
    if sx == sy %Si la matriz es cuadrada
        disp ('Las matrices son cuadradas.')
        
        Size = sx; %dimensi�n de ambas matrices
        d = zeros(Size,Size); %matriz resultante
        i = 1; %indice de rengl�n de d
        j = 1; %�ndice de columna de d
        ax = 1; %indice de rengl�n de a
        ab = 1; %�ndice de columna de a, e �ndice de rengl�n de b. En la multiplicaci�n de matrices, los elementos a operar siempre comparten un �ndice de columna (a) con el �ndice del rengl�n del otro (b) en todos los casos,
        by = 1; %�ndice de columna de b
        
        for ax = 1:Size %el rengl�n de a es el �ltimo en incrementarse hasta igualar el tama�o de las matrices, por lo que cuando sea igual a Size, nos indica que el sistema se encuentra en el �ltimo ciclo de la multiplicaci�n
            for by = 1:Size %este �ndice debe incrementarse y posteriormente cambiar intermitentemente cada Size veces
                ResultadoSuma = 0; %acumulador para el resultado de la suma de las multiplicaciones entre elementos
                for ab = 1:Size %este �ndice se incrementa o reinicia en cada una de las partes de la multiplicaci�n
                    Elemento1 = a(ax,ab);
                    Elemento2 = b(ab,by);
                    ResultadoSuma = ResultadoSuma + Elemento1*Elemento2; %se almacena en c cada resultado de la multiplicaci�n Elemento1*Elemento2
                end
                %Por �ltimo, se almacena el resultado de la suma en cierta posici�n de la matriz resultante
                d(i,j) = ResultadoSuma; %se almacena cada resultado en la posici�n dictada por los �ndices
                if j ~= Size %se ajustan los �ndices para ir llenando cada espacio
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
    disp ('Error. Las matrices no son del mismo tama�o.')
end


    