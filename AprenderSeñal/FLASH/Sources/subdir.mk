################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/ButtonDriver.c" \
"../Sources/Correlacion.c" \
"../Sources/Funciones.c" \
"../Sources/LedDriver.c" \
"../Sources/PIT.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/ButtonDriver.c \
../Sources/Correlacion.c \
../Sources/Funciones.c \
../Sources/LedDriver.c \
../Sources/PIT.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ADC.o \
./Sources/ButtonDriver.o \
./Sources/Correlacion.o \
./Sources/Funciones.o \
./Sources/LedDriver.o \
./Sources/PIT.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/ButtonDriver.d \
./Sources/Correlacion.d \
./Sources/Funciones.d \
./Sources/LedDriver.d \
./Sources/PIT.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/ButtonDriver.o" \
"./Sources/Correlacion.o" \
"./Sources/Funciones.o" \
"./Sources/LedDriver.o" \
"./Sources/PIT.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/ButtonDriver.d" \
"./Sources/Correlacion.d" \
"./Sources/Funciones.d" \
"./Sources/LedDriver.d" \
"./Sources/PIT.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/ButtonDriver.o \
./Sources/Correlacion.o \
./Sources/Funciones.o \
./Sources/LedDriver.o \
./Sources/PIT.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ButtonDriver.o: ../Sources/ButtonDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ButtonDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ButtonDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Correlacion.o: ../Sources/Correlacion.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Correlacion.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Correlacion.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Funciones.o: ../Sources/Funciones.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Funciones.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Funciones.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LedDriver.o: ../Sources/LedDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LedDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LedDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PIT.o: ../Sources/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	chcp 1252 > nul
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


