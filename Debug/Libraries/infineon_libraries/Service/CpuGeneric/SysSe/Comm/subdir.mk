################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.c \
../Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.c 

OBJS += \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.o \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.src \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.src 

C_DEPS += \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Console.d \
./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/%.src: ../Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fD:/FSKR/delta_ws/delta/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/%.o: ./Libraries/infineon_libraries/Service/CpuGeneric/SysSe/Comm/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


