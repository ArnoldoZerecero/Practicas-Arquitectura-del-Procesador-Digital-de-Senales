################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/DFT.c" \
"../Sources/PIT.c" \
"../Sources/SinCosAngle.c" \
"../Sources/SinCosTable.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/DFT.c \
../Sources/PIT.c \
../Sources/SinCosAngle.c \
../Sources/SinCosTable.c \
../Sources/main.c \

OBJS += \
./Sources/ADC.o \
./Sources/DFT.o \
./Sources/PIT.o \
./Sources/SinCosAngle.o \
./Sources/SinCosTable.o \
./Sources/main.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/DFT.d \
./Sources/PIT.d \
./Sources/SinCosAngle.d \
./Sources/SinCosTable.d \
./Sources/main.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/DFT.o" \
"./Sources/PIT.o" \
"./Sources/SinCosAngle.o" \
"./Sources/SinCosTable.o" \
"./Sources/main.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/DFT.d" \
"./Sources/PIT.d" \
"./Sources/SinCosAngle.d" \
"./Sources/SinCosTable.d" \
"./Sources/main.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/DFT.o \
./Sources/PIT.o \
./Sources/SinCosAngle.o \
./Sources/SinCosTable.o \
./Sources/main.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/DFT.o: ../Sources/DFT.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/DFT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/DFT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PIT.o: ../Sources/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SinCosAngle.o: ../Sources/SinCosAngle.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SinCosAngle.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SinCosAngle.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SinCosTable.o: ../Sources/SinCosTable.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SinCosTable.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SinCosTable.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '


