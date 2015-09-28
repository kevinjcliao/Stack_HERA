################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../HERA_main.cc 

OBJS += \
./HERA_main.o 

CC_DEPS += \
./HERA_main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/courses/include -I/home/courses/lib/HERA-C -O0 -g3 -Wall -c -fmessage-length=0 -Wno-unused-function -Wno-unused-label -Wno-unused-variable -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


