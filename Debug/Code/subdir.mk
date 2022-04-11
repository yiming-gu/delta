################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Code/ccu6_pwm.c \
../Code/hall.c \
../Code/motor.c \
../Code/move_filter.c \
../Code/pid.c 

OBJS += \
./Code/ccu6_pwm.o \
./Code/hall.o \
./Code/motor.o \
./Code/move_filter.o \
./Code/pid.o 

COMPILED_SRCS += \
./Code/ccu6_pwm.src \
./Code/hall.src \
./Code/motor.src \
./Code/move_filter.src \
./Code/pid.src 

C_DEPS += \
./Code/ccu6_pwm.d \
./Code/hall.d \
./Code/motor.d \
./Code/move_filter.d \
./Code/pid.d 


# Each subdirectory must supply rules for building sources it contributes
Code/%.src: ../Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fD:/FSKR/delta_ws/delta/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Code/%.o: ./Code/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


