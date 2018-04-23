clc
clear all

delete(instrfind);
SerialHandler = serial('COM3');
set(SerialHandler,'BaudRate',128000);
SizeBuffer = 1000;
xLabels = [0,650, 1300, 1950, 2600, 3250, 3900, 4550, 5200, 5850, 6500]; %Números del eje x al plotear la fase
SerialHandler.InputBufferSize = SizeBuffer;
fopen(SerialHandler);
while(1)
    BufferSonido = fread(SerialHandler, SizeBuffer, 'uint8'); %Se lee el resultado que regresa el micro
    
    Transformada = fft(BufferSonido);
    Transformada(1) = 0; %Se desprecian los primeros 2 valores
    Transformada(2) = 0;
    Fase = Transformada.*conj(Transformada)/length(BufferSonido) + 1; %De esta forma Fase incluye primera mitad de la transformada
    
    subplot(2,1,1);
    plot(BufferSonido)
    xlabel('Tiempo(muestras)')
    subplot(2,1,2);
    plot(Fase(1:SizeBuffer/2));
    xlabel('Frecuencia(Hz)')
    set(gca, 'XTickLabel', xLabels); %Se cambian los números del eje x por loss del arreglo
    pause(0.001);
end
fclose(SerialHandler);

