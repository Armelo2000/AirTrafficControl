################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ATC.cpp \
../src/Aircraft.cpp \
../src/DataParser.cpp \
../src/SystemManager.cpp 

CPP_DEPS += \
./src/ATC.d \
./src/Aircraft.d \
./src/DataParser.d \
./src/SystemManager.d 

OBJS += \
./src/ATC.o \
./src/Aircraft.o \
./src/DataParser.o \
./src/SystemManager.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\melah\Documents\Fiverr\AirTrafficControl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ATC.d ./src/ATC.o ./src/Aircraft.d ./src/Aircraft.o ./src/DataParser.d ./src/DataParser.o ./src/SystemManager.d ./src/SystemManager.o

.PHONY: clean-src

