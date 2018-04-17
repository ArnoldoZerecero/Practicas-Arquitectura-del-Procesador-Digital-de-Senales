clc
clear all
y = [5,6,7,8]; %h(n)
n = length(y);
PrevArgs = zeros(1,n); %Buffer de entradas

SerialHandler = serial('COM3');
set(SerialHandler,'BaudRate',9600);
fopen(SerialHandler);

while(1)
    x = input('Inserte valor: ');
    Resultado = 0; %Variable de retorno
    if(x < 0) %Se cierra el script
        break
    end
    if(x < 256)
        fwrite(SerialHandler,x);
        
        for i = n:-1:2
            PrevArgs(i) = PrevArgs(i - 1); %Se recorren los datos del buffer de entrada, eliminando el más antiguo
            Resultado = PrevArgs(i)*y(i) + Resultado; %Se hacen n-1 sumas de productos entre los buffers
        end
        
        i = i - 1;
        PrevArgs(i) = x; %El nuevo argumento se guarda al principio del buffer de entrada
        Resultado = PrevArgs(i)*y(i) + Resultado %Se hace la última multiplicación
        
        ResultadoMCU = fscanf(SerialHandler, '%c', 6) %Se leen un 6 chars desde el micro
    else
        disp('Error. Inserte un número de 8 bits')
    end

end

fclose(SerialHandler);
