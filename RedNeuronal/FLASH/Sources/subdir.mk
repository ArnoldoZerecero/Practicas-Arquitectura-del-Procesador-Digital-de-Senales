################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/FuncionesActivacion.c" \
"../Sources/RedNeuronal.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/FuncionesActivacion.c \
../Sources/RedNeuronal.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/FuncionesActivacion.o \
./Sources/RedNeuronal.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/FuncionesActivacion.d \
./Sources/RedNeuronal.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/FuncionesActivacion.o" \
"./Sources/RedNeuronal.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/FuncionesActivacion.d" \
"./Sources/RedNeuronal.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/FuncionesActivacion.o \
./Sources/RedNeuronal.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/FuncionesActivacion.o: ../Sources/FuncionesActivacion.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/FuncionesActivacion.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/FuncionesActivacion.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/RedNeuronal.o: ../Sources/RedNeuronal.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/RedNeuronal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/RedNeuronal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


