################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseForm.cpp \
../src/Baseabout.cpp \
../src/BukkaMain.cpp \
../src/BukkaTrips.cpp \
../src/BukkaTripsEntry.cpp \
../src/MapForm.cpp 

OBJS += \
./src/BaseForm.o \
./src/Baseabout.o \
./src/BukkaMain.o \
./src/BukkaTrips.o \
./src/BukkaTripsEntry.o \
./src/MapForm.o 

CPP_DEPS += \
./src/BaseForm.d \
./src/Baseabout.d \
./src/BukkaMain.d \
./src/BukkaTrips.d \
./src/BukkaTripsEntry.d \
./src/MapForm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.2/include" -I"C:/Users/The0s/Desktop/Imperial/4th year/Bada/BukkaTrips/inc" -O0 -g -Wall -c -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.2/include" -I"C:/Users/The0s/Desktop/Imperial/4th year/Bada/BukkaTrips/inc" -O0 -g -Wall -E -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -o"C:/Users/The0s/Desktop/Imperial/4th year/BukkaTrip/repository/BukkaTrips/Target-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


