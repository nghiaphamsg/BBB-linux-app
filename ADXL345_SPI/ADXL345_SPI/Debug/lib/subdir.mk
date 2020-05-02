################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/ADXL345.cpp \
../lib/ADXL345_SPI.cpp \
../lib/BusDevice.cpp \
../lib/SPIDevice.cpp 

OBJS += \
./lib/ADXL345.o \
./lib/ADXL345_SPI.o \
./lib/BusDevice.o \
./lib/SPIDevice.o 

CPP_DEPS += \
./lib/ADXL345.d \
./lib/ADXL345_SPI.d \
./lib/BusDevice.d \
./lib/SPIDevice.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/usr/arm-linux-gnueabihf/include/c++/8 -I"/home/nekobot/Project/BeagleboneBlack_Debian/ADXL345_SPI/ADXL345_SPI/lib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


