clc
clear all
SerialHandler = serial('COM3');
set(SerialHandler,'BaudRate',9600);
fopen(SerialHandler);
while(1)
    Desfase = fscanf(SerialHandler, '%c', 4) %Se lee el resultado que regresa el micro
end
fclose(SerialHandler);

