clc 
clear all
ResultBuffer = zeros(1,5);
load('Vocales.mat');

%CompareVocal = CompareVocal/max(CompareVocal); %Normalizar 
A1 = A1/max(A1);
A2 = A2/max(A2);
E1 = E1/max(E1);
E2 = E2/max(E2);
I1 = I1/max(I1);
I2 = I2/max(I2);
O1 = O1/max(O1);
O2 = O2/max(O2);
U1 = U1/max(U1);
U2 = U2/max(U2);

CompareVocal = A2;

BufferA = xcorr(A1); %Autocorrelaciones
BufferE = xcorr(E1);
BufferI = xcorr(I1);
BufferO = xcorr(O1);
BufferU = xcorr(U1);

ComparisonA = xcorr(A1, CompareVocal); %Correlaciones
ComparisonE = xcorr(E1, CompareVocal);
ComparisonI = xcorr(I1, CompareVocal);
ComparisonO = xcorr(O1, CompareVocal);
ComparisonU = xcorr(U1, CompareVocal);

ResultBuffer(1) = abs(max(ComparisonA) - max(BufferA)); %Se comparan las diferencias de los promedios de energía entre las autocorrelaciones y las correlaciones
ResultBuffer(2) = abs(max(ComparisonE) - max(BufferE));
ResultBuffer(3) = abs(max(ComparisonI) - max(BufferI));
ResultBuffer(4) = abs(max(ComparisonO) - max(BufferO));
ResultBuffer(5) = abs(max(ComparisonU) - max(BufferU))

if (min(ResultBuffer) == ResultBuffer(1))
    disp ('La vocal detectada fue A')
elseif (min(ResultBuffer) == ResultBuffer(2))
    disp ('La vocal detectada fue E')
elseif (min(ResultBuffer) == ResultBuffer(3))
    disp ('La vocal detectada fue I')
elseif (min(ResultBuffer) == ResultBuffer(4))
    disp ('La vocal detectada fue O')
else
    disp ('La vocal detectada fue U')
end


