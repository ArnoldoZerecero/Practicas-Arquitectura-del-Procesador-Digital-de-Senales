clc
clear all
NoPeriodChar = '0000';
SerialHandler = serial('COM3');
set(SerialHandler,'BaudRate',9600);
fopen(SerialHandler);
while(1)
    Periodo = fscanf(SerialHandler, '%c', 4); %Se lee el resultado que regresa el micro
    if(strcmp(Periodo,NoPeriodChar) == 1)
        disp('La senal no es periodica')
    else
        Periodo = Periodo
    end
end
fclose(SerialHandler);

