################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LocalizationManager.cpp \
../Location.cpp \
../Maps.cpp \
../Particle.cpp \
../ParticleSorter.cpp \
../RandomWalk.cpp \
../Robot.cpp \
../Utils.cpp \
../main.cpp 

OBJS += \
./LocalizationManager.o \
./Location.o \
./Maps.o \
./Particle.o \
./ParticleSorter.o \
./RandomWalk.o \
./Robot.o \
./Utils.o \
./main.o 

CPP_DEPS += \
./LocalizationManager.d \
./Location.d \
./Maps.d \
./Particle.d \
./ParticleSorter.d \
./RandomWalk.d \
./Robot.d \
./Utils.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


